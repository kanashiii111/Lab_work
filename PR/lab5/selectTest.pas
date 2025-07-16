program lab1;

type
  comparator = procedure(var arr: array of longint; i,j,minIndex: longint);

procedure selectCompUp(var arr: array of longint; i,j, minIndex : longint);
var
  temp: longint;
begin
  if arr[j] < arr[minIndex] then
    begin
      minIndex := j;
    end;
  if minIndex <> i then
  begin
    temp := arr[minIndex];
    arr[minIndex] := arr[i];
    arr[i] := temp;
  end;
end;

procedure selectCompDown(var arr: array of longint; i,j, minIndex : longint);
var
  temp: longint;
begin
  if arr[j] > arr[minIndex] then
    begin
      minIndex := j;
    end;
  if minIndex <> i then
  begin
    temp := arr[minIndex];
    arr[minIndex] := arr[i];
    arr[i] := temp;
  end;
end;


procedure selectCompDownTest(var arr: array of longint; i, minIndex, size : longint);
var
  temp: longint;
begin
  for j := i + 1 to size - 1 do begin
    if arr[j] > arr[minIndex] then
      begin
        minIndex := j;
      end;
    if minIndex <> i then
      begin
        temp := arr[minIndex];
        arr[minIndex] := arr[i];
        arr[i] := temp;
      end;
  end;
end;



procedure selectionSort(arr: array of longint; size: longint; var outputFile: TextFile; comp:comparator);
var
  i, j, minIndex: longint;
begin
  for i := 0 to size - 2 do
  begin
    minIndex := i;
    for j := i + 1 to size - 1 do
      comp(arr,i,j, minIndex);
  end;
  for i := 0 to size - 1 do
  begin
    Write(outputFile, arr[i]);
    if i < size-1 then Write(outputFile, ' ');
  end;
  Writeln(outputFile, '');
end;

var
  n: longint;
  outputFile: TextFile;
  inputFile: TextFile;
  arr: array of longint;
  i: longint;
begin
  Assign(outputFile, 'output.txt');
  Rewrite(outputFile);
  Assign(inputFile, 'test.txt');
  Reset(inputFile);
  Read(inputFile, n);
  SetLength(arr, n);
  for i := 0 to n - 1 do
  begin
    Read(inputFile, arr[i]);
  end;
  selectionSort(arr, n, outputFile, @selectCompUp);
  Close(inputFile);
  Close(outputFile);
end.