program lab5;

const
  MAX_SIZE = 20;

type
  TMatrix = array[1..MAX_SIZE, 1..MAX_SIZE] of integer;

var
  IncidenceMatrix, AdjacencyMatrix, AdjacencyMatrix2, AdjacencyMatrix3, AdjacencyMatrix4: TMatrix;
  ReachabilityMatrix, ConnectivityMatrix: TMatrix;
  N, M: integer;
  inputFile: TextFile;

procedure ReadIncidenceMatrix;
var
  i, j: integer;
begin
  Assign(inputFile, 'matrix_lab5.txt');
  Reset(inputFile);
  Readln(inputFile, N, M);
  
  for i := 1 to N do
    for j := 1 to M do
      Read(inputFile, IncidenceMatrix[i, j]);
  
  Close(inputFile);
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

procedure BuildAdjacencyMatrix;
var
  start, finish, i, j: integer;
begin
  for i := 1 to N do
    for j := 1 to N do
      AdjacencyMatrix[i, j] := 0;

  for j := 1 to M do
  begin
    start := 0;
    finish := 0;
    
    for i := 1 to N do
    begin
      if IncidenceMatrix[i, j] = 1 then start := i;
      if IncidenceMatrix[i, j] = -1 then finish := i;
    end;
    
    if (start > 0) and (finish > 0) then
      AdjacencyMatrix[start, finish] := 1;
  end;
end;

procedure BuildReachabilityMatrix;
var
  i, j, k: integer;
begin
  for i := 1 to N do
    for j := 1 to N do
      if (i = j) or (AdjacencyMatrix[i, j] = 1) then
        ReachabilityMatrix[i, j] := 1
      else
        ReachabilityMatrix[i, j] := 0;

  for k := 1 to N do
    for i := 1 to N do
      for j := 1 to N do
        if ReachabilityMatrix[i, j] = 0 then
          ReachabilityMatrix[i, j] := ReachabilityMatrix[i, k] * ReachabilityMatrix[k, j];
end;

procedure BuildConnectivityMatrix;
var
  i, j: integer;
begin
  for i := 1 to N do
    for j := 1 to N do
    begin
      if (ReachabilityMatrix[i, j] = 1) or (ReachabilityMatrix[j, i] = 1) then
        ConnectivityMatrix[i, j] := 1
      else
        ConnectivityMatrix[i, j] := 0;
    end;
end;

function IsConnected: boolean;
var
  i, j: integer;
begin
  Result := True;
  for i := 1 to N do
    for j := 1 to N do
      if ConnectivityMatrix[i, j] = 0 then
      begin
        Result := False;
        Exit;
      end;
end;

begin
  //Считываем матрицу инцидентности
  ReadIncidenceMatrix;
  PrintMatrix(IncidenceMatrix, N, 'Матрица инцидентности');

  //Преобразуем в матрицу смежности
  BuildAdjacencyMatrix;
  PrintMatrix(AdjacencyMatrix, N, 'Матрица смежности (A)');

  //Строим матрицу достижимости
  BuildReachabilityMatrix;
  PrintMatrix(ReachabilityMatrix, N, 'Матрица достижимости');

  //Строим матрицу связности
  BuildConnectivityMatrix;
  PrintMatrix(ConnectivityMatrix, N, 'Матрица связности');
  
  if IsConnected then
    Writeln('Граф является односторонне связным')
  else
    Writeln('Граф НЕ является односторонне связным');
end.