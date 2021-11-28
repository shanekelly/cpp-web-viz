var canvas;
var context;
var circles_to_render = [];  // All circles that should be rendered.
var polygons_to_render = [];  // All polygons that should be rendered.

// Define the callback function to run once the browser window is opened or when the page is
// refreshed.
window.onload = function() {
  setup();
};

/*
 * @brief - Creates the web socket connection and defines global variables.
 */
function setup() {
  // Get the canvas and 2D context.
  canvas = document.getElementById("canvas");

  context = canvas.getContext("2d");

  // Create a web socket and connect to the specified localhost port.
  let web_socket = new WebSocket("ws://localhost:9002");

  // Define the callback function that is run every time a message is received over the web socket.
  web_socket.onmessage = function (message_event) {
    let message_text = message_event.data;
    // Parse the text from the received message into a JSON object.
    let message_json = JSON.parse(message_text);
    let message_type = message_json.message_type;
    let message_data = message_json.message_data;

    switch (message_type) {
      case "PingMessage":
        web_socket.send(message_text);

        break;

      case "SetCanvasSizeMessage":
        let canvas_height = message_data.canvas_height;
        let canvas_width = message_data.canvas_width;
        canvas.setAttribute("height", canvas_height);
        canvas.setAttribute("width", canvas_width);

        break;

      case "SetFpsMessage":
        let fps = message_data.frames_per_second;
        document.getElementById("fps").innerHTML = fps;

        break;

      case "SetRenderablesMessage":
        context.clearRect(0, 0, canvas.width, canvas.height);

        // Update the arrays of renderables by calling the factory function to convert all the JSON
        // object representations of into proper renderable class instances.
        polygons_to_render =
          message_data.polygons_to_render.map(polygon_json => (new Polygon()).fromJson(polygon_json));
        circles_to_render =
          message_data.circles_to_render.map(circle_json => (new Circle()).fromJson(circle_json));

        // Render everything to the browser screen.
        renderAll();

        break;

      default:
        console.log("Message type \"" + message_type + "\" not supported.");
    }
  };

  // Define the callback function that is run every time the web socket connection is opened.
  web_socket.onopen = function() {
    // Send a log that the web socket connection has opened.
    console.log("The web socket connection has opened!");
  };

  // Define the callback function that is run every time the web socket connection is closed.
  web_socket.onclose = function() {
    // Send a log and alert that the web socket connection has been closed. This might happen if the
    // user manually terminates the C++ server.
    let message = "The web socket connection has closed!";
    console.log(message);
    alert(message);
  };

  canvas.onmousemove = function (mouse_event) {
    if (mouse_event) {
      let canvas_rect = canvas.getBoundingClientRect();
      let set_mouse_position_message = {
        message_type: "SetMousePositionMessage",
        message_data: {
          mouse_position_x: mouse_event.clientX - canvas_rect.left,
          mouse_position_y: mouse_event.clientY - canvas_rect.top
        }
      };
      let message_text = JSON.stringify(set_mouse_position_message);
      web_socket.send(message_text);
    }
  };

  window.onkeydown = function (key_event) {
    if (key_event) {
      let set_keyboard_key_state_message = {
        message_type: "SetKeyboardKeyStateMessage",
        message_data: {
          key_code: key_event.keyCode,
          is_pressed: true
        }
      };
      let message_text = JSON.stringify(set_keyboard_key_state_message);
      web_socket.send(message_text);
    }
  };

  window.onkeyup = function (key_event) {
    if (key_event) {
      let set_keyboard_key_state_message = {
        message_type: "SetKeyboardKeyStateMessage",
        message_data: {
          key_code: key_event.keyCode,
          is_pressed: false
        }
      };
      let message_text = JSON.stringify(set_keyboard_key_state_message);
      web_socket.send(message_text);
    }
  };
}

/*
 * @brief - Renders everything to the browser.
 */
function renderAll() {
  // Call each circle's render function.
  circles_to_render.forEach(circle => circle.render(context));
  // Call each polygon's render function.
  polygons_to_render.forEach(polygon => polygon.render(context));
}
