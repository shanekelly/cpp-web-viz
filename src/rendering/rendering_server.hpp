#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <string>

#include "rendering/polygon.hpp"

namespace sw {

class RenderingServer {
 public:
  RenderingServer();

  virtual void SetUp() = 0;

  virtual void Update() = 0;

  /*
   * @brief - The callback function to call when the web socket connection is opened.
   */
  void OnOpen(websocketpp::connection_hdl connection_handler);

  /*
   * @brief - The callback function to call when the web socket connection is closed.
   */
  void OnClose(websocketpp::connection_hdl connection_handler);

  /*
   * @param message_text - The message to send to the web browser client.
   */
  void SendTextToRenderingClient(const std::string& message_text);

  void WebSocketSpin();

  void UpdateSpin();

  /*
   * @brief - The main server functionality, where it will spin to maintain web socket connections.
   */
  void Run(const Hz& update_rate);

  /*
   * @brief - Clear all the rendering containers.
   */
  void ClearRendering();

  void PrepareToRender(const Polygon& polygon);

  /*
   * @brief - Compute the relevant rendering information from the costmap and store it in the
   * rendering containers.
   */
  void RenderAll();

 private:
  // The actual server.
  websocketpp::server<websocketpp::config::asio> server_;

  std::unique_ptr<std::thread> web_socket_thread_;
  std::unique_ptr<std::thread> update_spin_thread_;

  // The connection handler to the client, which is the web browser that we are rendering in.
  websocketpp::connection_hdl client_connection_handler_;

  // Whether or not the client has been connected yet.
  bool client_connected_ = false;

  std::chrono::microseconds update_period_;

  // Rendering containers.
  std::vector<Polygon> polygons_to_render_;  // All the polygons to render.
};

}  // namespace sw