class Polygon {
  /*
   * @param {[Point]} vertices
   * @param {string} edge_color - The color of the edges of the polygon in the format of a CSS color
   * value (see: https://developer.mozilla.org/en-US/docs/Web/CSS/color_value). RGBA format is
   * "rgb(#,#,#,#)"
   * @param {string} fill_color - The color of the inside of the polygon in the format of a CSS color
   * value (see: https://developer.mozilla.org/en-US/docs/Web/CSS/color_value). RGBA format is
   * "rgba(#,#,#,#)"
   */
  constructor(vertices, edge_color, fill_color) {
    this.vertices = vertices;
    this.edge_color = edge_color;
    this.fill_color = fill_color;
  }

  /*
   * @param {Object} polygon_json - A JSON object to create a Polygon from.
   * @returns {Polygon} - A Polygon object that was created from the specified JSON object.
   */
  fromJson(polygon_json) {
    this.vertices = polygon_json.vertices.map(point_json => (new Point()).fromJson(point_json));
    let ec = polygon_json.edge_color;
    this.edge_color = 'rgba(' + ec.r + ',' + ec.g + ',' + ec.b + ',' + ec.a + ')';
    let fc = polygon_json.fill_color;
    this.fill_color = 'rgba(' + fc.r + ',' + fc.g + ',' + fc.b + ',' + fc.a + ')';

    return this;
  }

  /*
   * @brief - Renders the polygon.
   * @param {CanvasRenderingContext2D} context - The rendering context to render the polygon to.
   */
  render(context) {
    context.strokeStyle = this.edge_color;
    context.fillStyle = this.fill_color;

    context.beginPath();
    let firstVertex = this.vertices[0];
    context.moveTo(firstVertex.x, firstVertex.y);
    for (let vertex_idx = 1; vertex_idx < this.vertices.length; ++vertex_idx) {
      let currVertex = this.vertices[vertex_idx];
      context.lineTo(currVertex.x, currVertex.y);
    }
    context.closePath();

    context.stroke();
    context.fill();
  }
}
