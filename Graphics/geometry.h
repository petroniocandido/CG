struct point2d {
       int x, y;
}

class Line {
   protected:
      point2d *points;
      int numPoints;
      int color;
      
   public:
      void lineTo(point2d a, point2d b);
      void draw();
             
}

class Polygon : Line {
   protected:
      int fillColor;
   public:
}
