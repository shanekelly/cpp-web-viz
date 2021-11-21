#include <cpp_web_viz/rendering/rendering_server.hpp>

#include <iostream>

#include <nlohmann/json.hpp>

#include <cpp_web_viz/rendering/messages.hpp>
#include <cpp_web_viz/rendering/rgba.hpp>

namespace cpp_web_viz {

RenderingServer::RenderingServer()
{
  // websocketpp::endpoint::clear_acess_channels(websocketpp::log::alevel::all);

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

void RenderingServer::OnOpen(websocketpp::connection_hdl connection_handler)
{
  client_connection_handler_ = connection_handler;
  client_connected_ = true;

  SetCanvasSizeMessage set_canvas_size_message(canvas_width_, canvas_height_);
  SendMessageToRenderingClient(set_canvas_size_message);

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
      Update();
    }
    std::this_thread::sleep_for(update_period_);
  }
}

void RenderingServer::Run(const int canvas_width, const int canvas_height, const Hz& update_rate)
{
  canvas_width_ = canvas_width;
  canvas_height_ = canvas_height;
  update_period_ = std::chrono::microseconds(std::lround(MICROSECONDS_PER_SECOND / update_rate));

  web_socket_thread_ = std::make_unique<std::thread>(&RenderingServer::WebSocketSpin, this);
  update_spin_thread_ = std::make_unique<std::thread>(&RenderingServer::UpdateSpin, this);

  update_spin_thread_->join();
  web_socket_thread_->join();
}

void RenderingServer::ClearRendering()
{
  polygons_to_render_.clear();
}

void RenderingServer::PrepareToRenderPolygon(const Polygon& polygon)
{
  polygons_to_render_.emplace_back(polygon);
}

void RenderingServer::RenderAll()
{
  SetRenderablesMessage set_renderables_message(polygons_to_render_);
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

}  // namespace cpp_web_viz
