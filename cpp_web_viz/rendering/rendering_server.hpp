#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <string>

#include <cpp_web_viz/rendering/messages.hpp>
#include <cpp_web_viz/rendering/polygon.hpp>

namespace cpp_web_viz {

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

  void OnMessage(websocketpp::connection_hdl connection_handler,
    websocketpp::server<websocketpp::config::asio>::message_ptr message);

  /*
   * @param message_text - The text to send to the web browser client.
   */
  void SendTextToRenderingClient(const std::string& message_text);

  template <class MessageType>
  void SendMessageToRenderingClient(const MessageType& message);

  void WebSocketSpin();

  void UpdateSpin();

  /*
   * @brief - The main server functionality, where it will spin to maintain web socket connections.
   */
  void Run(const int canvas_width, const int canvas_height, const Hz& update_rate);

  /*
   * @brief - Clear all the rendering containers.
   */
  void ClearRendering();

  void PrepareToRenderCircle(const Circle& circle);

  void PrepareToRenderPolygon(const Polygon& polygon);

  /*
   * @brief - Compute the relevant rendering information from the costmap and store it in the
   * rendering containers.
   */
  void RenderAll();

  const int GetCanvasWidth() const;

  const int GetCanvasHeight() const;

  const PositionInPixels& GetMousePosition() const;

  bool IsKeyPressed(const KeyCode key_code) const;

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

  int canvas_width_;
  int canvas_height_;

  PositionInPixels mouse_position_;

  std::unordered_map<KeyCode, bool> keyboard_state_;

  // All the renderables.
  std::vector<Circle> circles_to_render_;  // All the circles to render.
  std::vector<Polygon> polygons_to_render_;  // All the polygons to render.
};

}  // namespace cpp_web_viz
