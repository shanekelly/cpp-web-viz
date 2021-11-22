#include <iostream>

#include <cpp_web_viz/rendering/rendering_server.hpp>

using namespace cpp_web_viz;

static const int CANVAS_WIDTH = 800;
static const int CANVAS_HEIGHT = 400;
static const Hz UPDATE_FREQUENCY = 60;
static const TimeInSeconds UPDATE_PERIOD = 1.0f / UPDATE_FREQUENCY;

struct Disk
{
  float radius = 50;
  PositionInPixels position{CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2};

  static constexpr float speed = 200;  // Pixels per second.
};

class MyRenderingServer : public RenderingServer
{
  void SetUp() override
  {
  }

  void UpdateDisk(Disk& disk)
  {
    if (IsKeyPressed(KeyCode::LeftArrow)) {
      disk.position.x -= Disk::speed * UPDATE_PERIOD;
    }
    if (IsKeyPressed(KeyCode::RightArrow)) {
      disk.position.x += Disk::speed * UPDATE_PERIOD;
    }
    if (IsKeyPressed(KeyCode::UpArrow)) {
      disk.position.y -= Disk::speed * UPDATE_PERIOD;
    }
    if (IsKeyPressed(KeyCode::DownArrow)) {
      disk.position.y += Disk::speed * UPDATE_PERIOD;
    }

    // If the disk's new position is off the screen, then clamp it back inside the screen.
    disk.position.x = std::clamp(disk.position.x, disk.radius, GetCanvasWidth() - disk.radius);
    disk.position.y = std::clamp(disk.position.y, disk.radius, GetCanvasHeight() - disk.radius);
  }

  void PrepareToRenderDisk(const Disk& disk)
  {
    // The web client only knows how to render circles (not disks), so create a circle that
    // visually represents the disk so that the client knows how to render it.
    const RGBA circle_edge_color = Color::Blue;
    const RGBA circle_fill_color = Color::Blue;
    Circle circle(disk.position, disk.radius, circle_edge_color, circle_fill_color);

    // Prepare to send the circle to the client for rendering.
    PrepareToRenderCircle(circle);
  }

  void Update() override
  {
    // Remove any circles that were rendered in previous frames.
    ClearRendering();

    // Move the disk based on the arrow keys that are pressed.
    UpdateDisk(disk_);
    // Create a renderable circle from the disk and prepare to render it.
    PrepareToRenderDisk(disk_);

    // Send all circles that have been prepared for rendering to the web client to be rendered.
    RenderAll();
  }

  Disk disk_;
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
