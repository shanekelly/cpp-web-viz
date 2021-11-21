class Point {
  /*
   * @param {number} x - The x position of the point.
   * @param {number} y - The y position of the point.
   */
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  /*
   * @param {Object} point_json - A JSON object to create a Point from.
   * @returns {Point} - A Point object that was created from the specified JSON object.
   */
  fromJson(point_json) {
    this.x = point_json.x;
    this.y = point_json.y;

    return this;
  }
}
