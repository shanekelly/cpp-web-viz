var canvas;
var context;
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
  // Create a web socket and connect to the specified localhost port.
  let web_socket = new WebSocket("ws://localhost:9002");

  // Define the callback function that is run every time a message is received over the web socket.
  web_socket.onmessage = function (evt) {
    // Parse the text from the received message into a JSON object.
    let message_json = JSON.parse(evt.data);

    context.clearRect(0, 0, canvas.width, canvas.height);

    // Update the array of polygons to render by calling the factory function to convert all the
    // JSON object representations of polygons into proper Polygon class instances.
    polygons_to_render =
      message_json.polygons.map(polygon_json => (new Polygon()).fromJson(polygon_json));

    // Render everything to the browser screen.
    renderAll();
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

  // Get the canvas and 2D context.
  canvas = document.getElementById("vis");
  context = canvas.getContext("2d");
}

/*
 * @brief - Renders everything to the browser.
 */
function renderAll() {
  // Call each polygon's render function.
  polygons_to_render.forEach(polygon => polygon.render(context));
}
