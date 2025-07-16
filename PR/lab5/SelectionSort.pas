program lab1;

type
  comparator = function(first, second:longint): Boolean;
'''
function selectionComparatorUp(first, second: longint): Boolean;
begin
  selectionComparatorUp := first < second;
end;

function selectionComparatorDown(first, second: longint): Boolean;
begin
  selectionComparatorDown := first > second;
end;
'''
procedure selectCompUp(arr: array of longint; i,j : longint);
var
  minIndex: integer;
  temp: integer;
begin
  if arr[j] < arr[minIndex] then
    begin
      minIndex := j;
    end;
  end;
  if minIndex <> i then
  begin
    temp := arr[minIndex];
    arr[minIndex] := arr[i];
    arr[i] := temp;
  end;
end;

procedure selectionSort(arr: array of longint; size: longint; var outputFile: TextFile; comp:comparator);
var
  i, j, minIndex, temp: longint;
begin
  for i := 0 to size - 2 do
  begin
    minIndex := i;
    for j := i + 1 to size - 1 do
    '''
    begin
      if comp(arr[j], arr[minIndex]) then
      begin
        minIndex := j;
      end;
    end;
    if minIndex <> i then
    begin
      temp := arr[minIndex];
      arr[minIndex] := arr[i];
      arr[i] := temp;
    end;
    '''
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
  Assign(inputFile, 'input.txt');
  Reset(inputFile);
  Read(inputFile, n);
  SetLength(arr, n);
  for i := 0 to n - 1 do
  begin
    Read(inputFile, arr[i]);
  end;
  selectionSort(arr, n, outputFile, @selectionComparatorUp);
  Close(inputFile);
  Close(outputFile);
end.