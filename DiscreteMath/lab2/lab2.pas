program lab2;

var
  i,j,k,size,power: integer;
  correctSize:integer;
  nodeSet: array [,] of integer;
  nodeSetSum: array of integer;
  setOfNode: set of integer;
  connectedNodes: array of set of integer;  
begin
  randomize;
  writeln('Введите размерность матрицы смежности:');
  correctSize:= 0;
  while (correctSize <> 1) do begin
    readln(size);
    if ((size <= 10) and (size >= 4)) then begin 
      correctSize:= 1;
    end else writeln('Размерность должна быть в промежутке [4:10]');
  end;
  
  // Индекс по столбцам
  
  writeln();
  write('   ');
  for i:=1 to size do begin
    write(i, ' ');
  end;
  writeln();
  writeln();
  
  // Создание матрицы смежности
  
  setLength(nodeSet, size, size);
  
  for i:=0 to size - 1 do begin
    write(i + 1, ' ');
    for j:=0 to size - 1 do begin
      nodeSet[i,j]:= random(2);
      write(' ', nodeSet[i,j]);
    end;
    writeln();
  end;  
  writeln();
  writeln('Введите нужную степень:');
  readln(power);
  writeln();
  
  // Перебор матрицы смежности по строкам и столбцам одного индекса для нахождения степени вершины графа (Сумма каждой веришны хранится в отдельной ячейке массива)
  
  setLength(nodeSetSum, size);
  
  for i:=0 to size - 1 do begin
    for j:=0 to size - 1 do begin
      nodeSetSum[j]:= nodeSetSum[j] + nodeSet[i,j] + nodeSet[j,i];
    end;
  end;
  
  // Поиск вершин с нужной степенью
  
  for i:=0 to size - 1 do begin
    //writeln(nodeSetSum[i]);
    if (nodeSetSum[i] = power) then 
      begin 
        Include(setOfNode, i + 1);
      end;
  end;
  
  // Поиск связей вершин с нужной степенью
  
  SetLength(connectedNodes, size);
  for i := 1 to size do
  begin
    if i in setOfNode then
    begin
      for j := 1 to size do
      begin
        if (nodeSet[i - 1, j - 1] = 1) or (nodeSet[j - 1, i - 1] = 1) then
        begin
          Include(connectedNodes[i - 1], j);
        end;
      end;
    end;
  end;

 // Вывод

  writeln('Множество вершин с заданной степенью: ', setOfNode);
  for i := 1 to size do
  begin
    if i in setOfNode then
    begin
      write('Вершина ', i, ' связана с: ');
      for k := 1 to size do
      begin
        if k in connectedNodes[i - 1] then
        begin
          write(k, ' ');
        end;
      end;
      writeln;
    end;
  end;

end.