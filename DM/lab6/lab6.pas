program lab6;

const
  MAX_SIZE = 20;

type
  TMatrix = array[1..MAX_SIZE, 1..MAX_SIZE] of integer;

var
  AdjacencyMatrix, TempMatrix, ResultMatrix: TMatrix;
  N: integer;
  inputFile: TextFile;
  startVertex, endVertex, pathLength, totalPaths: integer;

procedure ReadAdjMatrix;
var
  i, j: integer;
begin
  Assign(inputFile, 'matrix_lab6.txt');
  Reset(inputFile);
  Readln(inputFile, N);
  
  for i := 1 to N do
    for j := 1 to N do
      Read(inputFile, AdjacencyMatrix[i, j]);
  
end;

procedure PrintMatrix(const matrix: TMatrix; size: integer; name: string);
var
  i, j: integer;
begin
  Writeln(name, ':');
  Write('   ');
  for j := 1 to size do
    Write(j:3);
  Writeln;
  
  for i := 1 to size do
  begin
    Write(i:2, ' ');
    for j := 1 to size do
      Write(matrix[i, j]:3);
    Writeln;
  end;
  Writeln;
end;

procedure MultiplyMatrices(const A, B: TMatrix; var Result: TMatrix);
var
  sum, i, j, k: integer;
begin
  for i := 1 to N do
    for j := 1 to N do
    begin
      sum := 0;
      for k := 1 to N do
        sum := sum + A[i, k] * B[k, j];
      Result[i, j] := sum;
    end;
end;

procedure MatrixPower(const Matrix: TMatrix; power: integer; var Result: TMatrix);
var
  i, j: integer;
begin
  if power = 0 then
  begin
    for i := 1 to N do
      for j := 1 to N do
        if i = j then
          Result[i, j] := 1
        else
          Result[i, j] := 0;
    Exit;
  end;

  if power = 1 then
  begin
    for i := 1 to N do
      for j := 1 to N do
        Result[i, j] := Matrix[i, j];
    Exit;
  end;

  for i := 1 to N do
    for j := 1 to N do
      Result[i, j] := Matrix[i, j];

  for i := 2 to power do
  begin
    MultiplyMatrices(Result, Matrix, TempMatrix);
    Result := TempMatrix;
  end;
end;

function CountPaths(start, finish, length: integer): integer;
var
  i: integer;
  PowerMatrix: TMatrix;
begin
  MatrixPower(AdjacencyMatrix, length, PowerMatrix);
  Result := PowerMatrix[start, finish];
  write('Матрица в степени заданной длины ', length);
  PrintMatrix(PowerMatrix, N, ' ');
end;

begin
  ReadAdjMatrix;
  PrintMatrix(AdjacencyMatrix, N, 'Матрица смежности');
  Write('Введите номер начальной вершины (1..', N, '): ');
  Readln(startVertex);
  Write('Введите номер конечной вершины (1..', N, '): ');
  Readln(endVertex);
  Write('Введите длину пути (>=1): ');
  Readln(pathLength);
  writeln();
  totalPaths:= CountPaths(startVertex, endVertex, pathLength);
  Writeln('Кол-во путей длины ', pathLength, ' от вершины ', startVertex, 
          ' до вершины ', endVertex, ': ', totalPaths);
end.