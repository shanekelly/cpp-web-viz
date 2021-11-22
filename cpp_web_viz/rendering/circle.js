class Circle {
  /*
   * @param {Point} position
   * @param {number} radius
   * @param {string} edge_color - The color of the edges of the circle in the format of a CSS color
   * value (see: https://developer.mozilla.org/en-US/docs/Web/CSS/color_value). RGBA format is
   * "rgb(#,#,#,#)"
   * @param {string} fill_color - The color of the inside of the circle in the format of a CSS color
   * value (see: https://developer.mozilla.org/en-US/docs/Web/CSS/color_value). RGBA format is
   * "rgba(#,#,#,#)"
   */
  constructor(position, radius, edge_color, fill_color) {
    this.position = position;
    this.radius
    this.edge_color = edge_color;
    this.fill_color = fill_color;
  }

  /*
   * @param {Object} circle_json - A JSON object to create a Circle from.
   * @returns {Circle} - A Circle object that was created from the specified JSON object.
   */
  fromJson(circle_json) {
    this.position = (new Point()).fromJson(circle_json.position);
    this.radius = circle_json.radius;
    let ec = circle_json.edge_color;
    this.edge_color = 'rgba(' + ec.r + ',' + ec.g + ',' + ec.b + ',' + ec.a + ')';
    let fc = circle_json.fill_color;
    this.fill_color = 'rgba(' + fc.r + ',' + fc.g + ',' + fc.b + ',' + fc.a + ')';

    return this;
  }

  /*
   * @brief - Renders the circle.
   * @param {CanvasRenderingContext2D} context - The rendering context to render the circle to.
   */
  render(context) {
    context.strokeStyle = this.edge_color;
    context.fillStyle = this.fill_color;

    context.beginPath();
    context.arc(this.position.x, this.position.y, this.radius, 0, 2 * Math.PI, false);
    context.closePath();

    context.stroke();
    context.fill();
  }
}
