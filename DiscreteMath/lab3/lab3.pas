program lab3;

var
  inputFile: TextFile;
  i, j, n, m: integer;
  incidenceMatrix: array [,] of integer;
  inDegree: array of integer;
  minDegree: integer;
  vertices: array of integer;
  count: integer;
  vertexName: char;

begin
  Assign(inputFile, 'matrix.txt');
  Reset(inputFile);
  read(inputFile, n);
  read(inputFile, m);
  SetLength(incidenceMatrix, n, m);
  SetLength(inDegree, n);
  write(' ');
  for i := 0 to m-1 do begin
    write('  ', i + 1);
  end;
  writeln();
  for i := 0 to n-1 do begin
    vertexName := Chr(Ord('A') + i);
    inDegree[i] := 0;
    write(vertexName, ' ');
    for j := 0 to m-1 do begin
      read(inputFile, incidenceMatrix[i,j]);
      
      if (incidenceMatrix[i,j] = -1) or (incidenceMatrix[i,j] = 2) then
        inc(inDegree[i]);
      
      if (incidenceMatrix[i,j] <> -1) then begin
        write(' ', incidenceMatrix[i,j]);
      end else write(incidenceMatrix[i,j]);
        write(' ');
        
        
    end;
    writeln();
  end;
  Close(inputFile);


  // Находим минимальную полустепень захода
  minDegree := inDegree[0];
  for i := 1 to n-1 do
    if inDegree[i] < minDegree then
      minDegree := inDegree[i];

  // Находим все вершины с минимальной полустепенью захода
  SetLength(vertices, n);
  count := 0;
  for i := 0 to n-1 do
    if inDegree[i] = minDegree then
    begin
      vertices[count] := i;
      count := count + 1;
    end;

  // Вывод результатов  
  writeln('Вершины с минимальной полустепенью захода (', minDegree, '):');
  for i := 0 to count-1 do
  begin
    vertexName := Chr(Ord('A') + vertices[i]);
    write('Вершина ', vertexName, ': дуги {');
    
    // Находим все дуги, входящие в эту вершину
    var firstArc := true;
    for j := 0 to m-1 do
      if (incidenceMatrix[vertices[i],j] = -1) or (incidenceMatrix[vertices[i],j] = 2) then
      begin
        if not firstArc then write(', ');
        write(j+1);
        firstArc := false;
      end;
      writeln('}');
  end;
end.