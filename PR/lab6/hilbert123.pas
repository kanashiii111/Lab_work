program hilbert;

uses GraphABC, HilbertCurveUnit;

const
  MoveStep = 10;
  ZoomFactor = 1.01;

procedure KeyDown(key: integer);
begin
  case key of
    VK_P: IncreaseDepth;
    VK_M: DecreaseDepth;
    VK_A: MoveHilbert(-MoveStep, 0);
    VK_D: MoveHilbert(MoveStep, 0);
    VK_W: MoveHilbert(0, -MoveStep);
    VK_S: MoveHilbert(0, MoveStep);
    VK_Q: ZoomHilbert(1/ZoomFactor);
    VK_E: ZoomHilbert(ZoomFactor);
  end;
end;

begin
  SetWindowTitle('Кривая Гильберта');
  OnKeyDown := KeyDown;
  DrawHilbertCurve;
end.