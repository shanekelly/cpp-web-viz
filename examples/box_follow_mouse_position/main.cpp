#include <iostream>

#include <websocketpp/common/thread.hpp>

#include <cpp_web_viz/rendering/rendering_server.hpp>

using namespace cpp_web_viz;

static const int CANVAS_WIDTH = 900;
static const int CANVAS_HEIGHT = 900;
static const Hz UPDATE_FREQUENCY = 60;
static const TimeInSeconds UPDATE_PERIOD = 1.0f / UPDATE_FREQUENCY;

struct Box
{
  float size;
  PositionInPixels position;
};

class MyRenderingServer : public RenderingServer
{
  void SetUp() override
  {
    // Initialize the size and position of the box.
    const float box_size = 50;
    const PositionInPixels box_position{0, 0};
    box_ = Box{box_size, box_position};
  }

  void UpdateBox(Box& box)
  {
    // Update the box's position to be centered around the mouse.
    const PositionInPixels& mouse_position = GetMousePosition();
    box.position.x = mouse_position.x;
    box.position.y = mouse_position.y;

    // If the box's new position is off the screen, then clamp it back inside the screen.
    const float box_half_size = box.size / 2;
    box.position.x = std::clamp(box.position.x, box_half_size, GetCanvasWidth() - box_half_size);
    box.position.y = std::clamp(box.position.y, box_half_size, GetCanvasHeight() - box_half_size);
  }

  void PrepareToRenderBox(const Box& box)
  {
    // The web client only knows how to render polygons (not boxes), so create a polygon that
    // visually represents the box so that the client knows how to render it.
    const float box_half_size = box.size / 2;
    const std::vector<PositionInPixels> polygon_vertices{
      {box.position.x - box_half_size, box.position.y - box_half_size},
      {box.position.x - box_half_size, box.position.y + box_half_size},
      {box.position.x + box_half_size, box.position.y + box_half_size},
      {box.position.x + box_half_size, box.position.y - box_half_size}};
    const RGBA polygon_edge_color = Color::Red;
    const RGBA polygon_fill_color = Color::Red;
    Polygon polygon(polygon_vertices, polygon_edge_color, polygon_fill_color);

    // Prepare to send the polygon to the client for rendering.
    PrepareToRenderPolygon(polygon);
  }

  void Update() override
  {
    // Remove any polygons that were rendered in previous frames.
    ClearRendering();

    // Move the box to the mouse's position.
    UpdateBox(box_);
    // Create a renderable polygon from the box and prepare to render it.
    PrepareToRenderBox(box_);

    // Send all polygons that have been prepared for rendering to the web client to be rendered.
    RenderAll();
  }

  Box box_;
};

int main()
{
  try {
    // Create the server, which will connect with the web browser client to send rendering
    // information for visualization in the browser.
    MyRenderingServer rendering_server;
    rendering_server.Run(CANVAS_WIDTH, CANVAS_HEIGHT, UPDATE_FREQUENCY);
  } catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  }
}
