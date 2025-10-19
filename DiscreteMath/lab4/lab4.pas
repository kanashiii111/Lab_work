program lab4;

var
  inputFile: TextFile;
  i, j, n, m: integer;
  adjacencyMatrix: array [,] of integer;
  verticeNameToDelete: char;
  verticeToDelete: integer;
  verticeName: char;
begin
  Assign(inputFile, 'matrix_lab4.txt');
  Reset(inputFile);
  read(inputFile, n);
  read(inputFile, m);
  SetLength(adjacencyMatrix, n, m);
  write('  ');
  for i := 0 to m-1 do begin
    write(' ', i + 1);
  end;
  writeln();
  for i := 0 to n-1 do begin
    verticeName := Chr(Ord('A') + i);
    write(i + 1, ' ');
    for j := 0 to m-1 do begin
      read(inputFile, adjacencyMatrix[i,j]);
      write(' ', adjacencyMatrix[i,j]);
    end;
    writeln();
  end;
  Close(inputFile);
  writeln();
  writeln('Введите номер вершины для удаления:');
  readln(verticeNameToDelete);
  verticeToDelete:= Ord(verticeNameToDelete)- 48;
  writeln();
  write('  ');
  for i := 0 to m-1 do begin
    if (verticeToDelete <> i + 1) then write(' ', i + 1);
  end;
  writeln();
  for i := 0 to n-1 do begin
    verticeName := Chr(Ord('A') + i);
    if (verticeToDelete - 1 <> i) then
      write(i + 1, ' ');
    for j := 0 to m-1 do begin
      if ((verticeToDelete - 1 <> j) and (verticeToDelete - 1 <> i)) then
        write(' ', adjacencyMatrix[i,j]);
    end;
    if (verticeToDelete - 1 <> i) then writeln();
  end;

end.