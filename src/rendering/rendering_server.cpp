#include "rendering/rendering_server.hpp"

#include <iostream>

#include "nlohmann/json.hpp"

#include "rendering/rgba.hpp"

namespace cpp_web_viz {

static const int PIXELS_PER_METER = 80;

RenderingServer::RenderingServer() {
  // Initialize ASIO.
  server_.init_asio();

  // Register the handler callbacks.
  server_.set_open_handler(
    websocketpp::lib::bind(&RenderingServer::OnOpen, this, websocketpp::lib::placeholders::_1));
  server_.set_close_handler(
    websocketpp::lib::bind(&RenderingServer::OnClose, this, websocketpp::lib::placeholders::_1));
}

void RenderingServer::OnOpen(websocketpp::connection_hdl connection_handler) {
  client_connection_handler_ = connection_handler;
  client_connected_ = true;

  SetUp();
}

void RenderingServer::OnClose(websocketpp::connection_hdl connection_handler) {
  client_connected_ = false;
}

void RenderingServer::SendTextToRenderingClient(const std::string& message_text) {
  if (client_connected_) {
    server_.send(client_connection_handler_, message_text, websocketpp::frame::opcode::value::text);
  } else {
    std::cout << "Message not sent. There is no client connected." << std::endl;
  }
}

void RenderingServer::WebSocketSpin() {
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

void RenderingServer::UpdateSpin() {
  while (true) {
    if (client_connected_) {
      Update();
    }
    std::this_thread::sleep_for(update_period_);
  }
}

void RenderingServer::Run(const Hz& update_rate) {
  update_period_ = std::chrono::microseconds(std::lround(MICROSECONDS_PER_SECOND / update_rate));

  web_socket_thread_ = std::make_unique<std::thread>(&RenderingServer::WebSocketSpin, this);
  update_spin_thread_ = std::make_unique<std::thread>(&RenderingServer::UpdateSpin, this);

  update_spin_thread_->join();
  web_socket_thread_->join();
}

void RenderingServer::ClearRendering() {
  polygons_to_render_.clear();
}

void RenderingServer::PrepareToRender(const Polygon& polygon) {
  polygons_to_render_.emplace_back(polygon);
}

void RenderingServer::RenderAll() {
  nlohmann::json rendering_info;
  rendering_info["polygons"] = polygons_to_render_;
  const std::string& message_text = rendering_info.dump();
  SendTextToRenderingClient(message_text);
}

}  // namespace cpp_web_viz
