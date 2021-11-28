#include <cpp_web_viz/rendering/rendering_server.hpp>

#include <iostream>

#include <nlohmann/json.hpp>

#include <cpp_web_viz/messaging/ping_message.hpp>
#include <cpp_web_viz/messaging/set_canvas_size_message.hpp>
#include <cpp_web_viz/messaging/set_fps_message.hpp>
#include <cpp_web_viz/messaging/set_keyboard_key_state_message.hpp>
#include <cpp_web_viz/messaging/set_mouse_position_message.hpp>
#include <cpp_web_viz/messaging/set_renderables_message.hpp>
#include <cpp_web_viz/rendering/rgba.hpp>

namespace cpp_web_viz {

RenderingServer::RenderingServer()
{
  ping_period_ = std::chrono::nanoseconds(std::lround(NANOSECONDS_PER_SECOND * 1.0));
  last_ping_sent_timestamp_ = std::chrono::nanoseconds(0);

  // Initialize ASIO.
  server_.init_asio();

  // Register the handler callbacks.
  server_.set_open_handler(
    websocketpp::lib::bind(&RenderingServer::OnOpen, this, websocketpp::lib::placeholders::_1));
  server_.set_close_handler(
    websocketpp::lib::bind(&RenderingServer::OnClose, this, websocketpp::lib::placeholders::_1));
  server_.set_message_handler(
    websocketpp::lib::bind(&RenderingServer::OnMessage, this, websocketpp::lib::placeholders::_1,
      websocketpp::lib::placeholders::_2));

  // Disable websocketpp logging.
  server_.clear_access_channels(websocketpp::log::alevel::all);
}

void RenderingServer::SetUp()
{
}

void RenderingServer::Update()
{
}

void RenderingServer::OnOpen(websocketpp::connection_hdl connection_handler)
{
  client_connection_handler_ = connection_handler;
  client_connected_ = true;

  SetCanvasSizeMessage set_canvas_size_message(canvas_width_, canvas_height_);
  SendMessageToRenderingClient(set_canvas_size_message);

  SetFpsMessage set_fps_message(update_frequency_);
  SendMessageToRenderingClient(set_fps_message);

  SetUp();
}

void RenderingServer::OnClose(websocketpp::connection_hdl connection_handler)
{
  client_connected_ = false;
}

void RenderingServer::OnMessage(websocketpp::connection_hdl connection_handler,
  websocketpp::server<websocketpp::config::asio>::message_ptr message)
{
  nlohmann::json message_json = nlohmann::json::parse(message->get_payload());

  const std::string message_type = message_json.at("message_type");
  if (message_type == MessageType::SetMousePositionMessage) {
    const SetMousePositionMessage set_mouse_position_message =
      message_json.get<SetMousePositionMessage>();

    mouse_position_.x = set_mouse_position_message.mouse_position_x;
    mouse_position_.y = set_mouse_position_message.mouse_position_y;
  } else if (message_type == MessageType::SetKeyboardKeyStateMessage) {
    const SetKeyboardKeyStateMessage set_keyboard_key_state_message =
      message_json.get<SetKeyboardKeyStateMessage>();

    keyboard_state_[set_keyboard_key_state_message.key_code] =
      set_keyboard_key_state_message.is_pressed;
  } else if (message_type == MessageType::PingMessage) {
    const PingMessage ping_message = message_json.get<PingMessage>();
    const std::chrono::nanoseconds now_timestamp =
      std::chrono::high_resolution_clock::now().time_since_epoch();
    const std::chrono::nanoseconds roundtrip_ping_time =
      now_timestamp - ping_message.sent_timestamp;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Ping: " << roundtrip_ping_time.count() / NANOSECONDS_PER_MILLISECOND << " ms"
      << std::endl;
  } else {
    std::cout << "Server received unrecognized message type \"" << message_type <<
      "\" from the client!" << std::endl;
  }
}

void RenderingServer::InternalUpdate()
{
  const std::chrono::nanoseconds now_timestamp =
    std::chrono::high_resolution_clock::now().time_since_epoch();
  const std::chrono::nanoseconds time_since_last_ping_sent =
    now_timestamp - last_ping_sent_timestamp_;
  if (time_since_last_ping_sent > ping_period_) {
    const PingMessage ping_message(now_timestamp);
    SendMessageToRenderingClient(ping_message);
    last_ping_sent_timestamp_ = now_timestamp;
  }
}

void RenderingServer::SendTextToRenderingClient(const std::string& message_text)
{
  if (client_connected_) {
    server_.send(client_connection_handler_, message_text, websocketpp::frame::opcode::value::text);
  } else {
    std::cout << "Message not sent. There is no client connected." << std::endl;
  }
}

template <class MessageType>
void RenderingServer::SendMessageToRenderingClient(const MessageType& message)
{
  const std::string message_text = nlohmann::json(message).dump();
  SendTextToRenderingClient(message_text);
}

void RenderingServer::WebSocketSpin()
{
  // Listen on port 9002.
  server_.set_reuse_addr(true);
  server_.listen(9002);

  // Start the server accept loop.
  server_.start_accept();

  // Start the ASIO io_service run loop.
  try {
      server_.run();
  } catch (const std::exception & e) {
      std::cout << e.what() << std::endl;
  }
}

void RenderingServer::UpdateSpin()
{
  while (true) {
    if (client_connected_) {
      InternalUpdate();
      Update();
    }
    std::this_thread::sleep_for(update_period_);
  }
}

void RenderingServer::Run(const int canvas_width, const int canvas_height, const Hz& update_frequency)
{
  canvas_width_ = canvas_width;
  canvas_height_ = canvas_height;
  update_frequency_ = update_frequency;
  update_period_ = std::chrono::nanoseconds(std::lround(NANOSECONDS_PER_SECOND / update_frequency));

  web_socket_thread_ = std::make_unique<std::thread>(&RenderingServer::WebSocketSpin, this);
  update_spin_thread_ = std::make_unique<std::thread>(&RenderingServer::UpdateSpin, this);

  update_spin_thread_->join();
  web_socket_thread_->join();
}

void RenderingServer::ClearRendering()
{
  circles_to_render_.clear();
  polygons_to_render_.clear();
}

void RenderingServer::PrepareToRenderCircle(const Circle& circle)
{
  circles_to_render_.emplace_back(circle);
}

void RenderingServer::PrepareToRenderPolygon(const Polygon& polygon)
{
  polygons_to_render_.emplace_back(polygon);
}

void RenderingServer::RenderAll()
{
  SetRenderablesMessage set_renderables_message(circles_to_render_, polygons_to_render_);
  SendMessageToRenderingClient(set_renderables_message);
}

const int RenderingServer::GetCanvasWidth() const
{
  return canvas_width_;
}

const int RenderingServer::GetCanvasHeight() const
{
  return canvas_height_;
}

const PositionInPixels& RenderingServer::GetMousePosition() const
{
  return mouse_position_;
}

bool RenderingServer::IsKeyPressed(const KeyCode key_code) const
{
  if (!keyboard_state_.contains(key_code)) {
    return false;
  }

  return keyboard_state_.at(key_code);
}

}  // namespace cpp_web_viz
