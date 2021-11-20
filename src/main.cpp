#include <iostream>

#include <websocketpp/common/thread.hpp>

#include "rendering/rendering_server.hpp"

using namespace cpp_web_viz;

class MyRenderingServer : public RenderingServer
{
  void SetUp() override {
    polygon_ = {
      {{100, 100}, {200, 100}, {200, 200}, {100, 200}},
      {255, 0, 0, 1},
      {255, 0, 0, 1}};
  }

  void Update() override {
    ClearRendering();

    polygon_.Translate({1, 1});

    PrepareToRender(polygon_);

    RenderAll();
  }

  Polygon polygon_;
};

int main() {
  try {
    // Create the server, which will connect with the web browser client to send rendering
    // information for visualization.
    MyRenderingServer rendering_server;
    rendering_server.Run(60);
  } catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  }
}
