unit HilbertCurveUnit;

interface

uses GraphABC;

procedure DrawHilbertCurve;
procedure IncreaseDepth;
procedure DecreaseDepth;
procedure MoveHilbert(dx, dy: integer);
procedure ZoomHilbert(factor: real);

implementation

const
  MinDepth = 1;
  MaxDepth = 8;
  DefaultDepth = 4;
  BaseSize = 400;
  MoveStep = 10;
  ZoomFactor = 1.01;

var
  depth: integer = DefaultDepth;
  offsetX: integer = 0;
  offsetY: integer = 0;
  hilbertScale: real = 1.0;
  firstPoint: boolean;

procedure HilbertCurve(x, y, xi, xj, yi, yj, n: double);
var
  newX, newY: integer;
begin
  if n = 0 then 
  begin
    newX := Round(x + (xi + yi) / 2);
    newY := Round(y + (xj + yj) / 2);
    if firstPoint then
      begin
        MoveTo(newX,newY);
        firstPoint:= false;
      end
      else
        LineTo(newX, newY);
  end
  else
  begin
    HilbertCurve(x, y, yi / 2, yj / 2, xi / 2, xj / 2, n - 1);
    HilbertCurve(x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    HilbertCurve(x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    HilbertCurve(x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2, n - 1);
  end;
end;

procedure DrawHilbertCurve;
var
  size, startX, startY: integer;
begin
  LockDrawing;
  ClearWindow;
  
  size := Round(BaseSize * hilbertScale);
  startX := Round(150 * hilbertScale) + offsetX;
  startY := Round(100 * hilbertScale) + offsetY;
  
  firstPoint:= true;
  HilbertCurve(startX, startY, 0, size, size, 0, depth);
  
  TextOut(10, 10, 'Глубина: ' + depth.ToString);
  TextOut(10, 30, 'Масштаб: ' + hilbertScale.ToString('0.00'));
  TextOut(10, 50, 'WASD - перемещение, P/M - глубина, Q/E - масштаб');
  
  Redraw;
end;

procedure IncreaseDepth;
begin
  if depth < MaxDepth then
  begin
    depth += 1;
    DrawHilbertCurve;
  end;
end;

procedure DecreaseDepth;
begin
  if depth > MinDepth then
  begin
    depth -= 1;
    DrawHilbertCurve;
  end;
end;

procedure MoveHilbert(dx, dy: integer);
begin
  offsetX += dx;
  offsetY += dy;
  DrawHilbertCurve; 
end;

procedure ZoomHilbert(factor: real);
begin
  hilbertScale *= factor;
  if hilbertScale < 0.1 then hilbertScale := 0.1;
  if hilbertScale > 10.0 then hilbertScale := 10.0;
  DrawHilbertCurve;
end;
end.