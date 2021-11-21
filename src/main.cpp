#include <iostream>

#include <websocketpp/common/thread.hpp>

#include "rendering/rendering_server.hpp"

using namespace cpp_web_viz;

static const int CANVAS_HEIGHT = 400;
static const int CANVAS_WIDTH = 800;
// static const Hz UPDATE_PERIOD = 1 /

class Box
{
 public:
  Box()
    : x(0), y(0), vx(0), vy(0)
  {
  }

  Box(const float x_, const float y_, const float vx_, const float vy_)
    : x(x_), y(y_), vx(vx_), vy(vy_)
  {
  }

  float x, y, vx, vy;
};

class MyRenderingServer : public RenderingServer
{
  void SetUp() override {
    b_ = Box(10, 10, 1, 1);
  }

  void UpdateBox(Box& b)
  {
    const PositionInPixels& mp = GetMousePosition();
    b.x = mp.x;
    b.y = mp.y;
  }

  void PrepToRender(const Box& b)
  {
    const float half_size = 10;

    Polygon p(
      {
        {b.x - half_size, b.y - half_size},
        {b.x - half_size, b.y + half_size},
        {b.x + half_size, b.y + half_size},
        {b.x + half_size, b.y - half_size}
      },
      {255, 0, 0, 1},
      {255, 0, 0, 1});
    PrepareToRender(p);
  }

  void Update() override {
    ClearRendering();

    UpdateBox(b_);
    PrepToRender(b_);

    RenderAll();
  }

  Box b_;
};

int main() {
  try {
    // Create the server, which will connect with the web browser client to send rendering
    // information for visualization.
    MyRenderingServer rendering_server;
    rendering_server.Run(CANVAS_WIDTH, CANVAS_HEIGHT, 60);
  } catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  }
}
