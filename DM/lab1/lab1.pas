program lab1;

var 
    i: integer;
    input: integer;
    tempInt: integer;
    tempChar: char;
    element: string;
    power: integer;
    A,B,C,D,E,X,Y,K: set of string;

procedure powerCheck();
var
  correctPower: integer;
begin
  correctPower := 0;
  while (correctPower = 0) do begin
    try
      readln(&input);
      if (input > 10) then
        raise Exception.Create('Кол-во чисел множ-ва не может превышать 10.');
      correctPower:= 1;
    except
      on E: Exception do begin
        writeln(E.Message);
        writeln('Неправильный ввод, повторить попытку? (1 - да, 0 - нет)');
        readln(&tempInt);
        if (tempInt = 0) then begin
          if (input > 10) then input:= 10;
          correctPower:= 1;
        end;
      end;
    end;
  end;
end;

procedure inputCheck();
var
  correctInput: integer;
begin
  correctInput := 0;
  while (correctInput = 0) do begin
    try
      readln(&input);
      correctInput:= 1;
    except
      writeln('Неправильный ввод, повторить попытку? (1 - да, 0 - нет)');
      readln(&tempInt);
      if (tempInt = 0) then correctInput:= 1;
    end;
  end;
end;

Begin
  // Ввод множества натуральных чисел
  Writeln('Введите мощность A (Натуральные числа):');
  powerCheck();
  Writeln('Введите элементы:');
  power:= input;
  i := 0;
  while i < power do begin
    inputCheck();
    str(input, &element);
    if (input < 0) then begin
      writeln('Введенное число не натуральное');
    end else if (element in A) then begin
      Writeln('Элемент уже в множестве');
    end else begin
      Include(A, element);
      i := i + 1;
    end;
  end;
  // Ввод множества целых чисел
  Writeln('Введите мощность B (Целые числа):');
  powerCheck();
  Writeln('Введите элементы:');
  power:= input;
  i := 0;
  while i < power do begin
    inputCheck();
    str(input, &element);
    if (element in B) then begin
      Writeln('Элемент уже в множестве');
    end else begin
      Include(B, element);
      i := i + 1;
    end;
  end;
  Writeln('Введите мощность С (Рациональные числа):');
  powerCheck();
  Writeln('Введите элементы (В формате ЦЕЛОЕ, НАТУРАЛЬНОЕ со след. строки):');
  power:= input;
  i := 0;
  while i < power do begin
    inputCheck();
    str(input, &element);
    inputCheck();
    element:= element + '/' + floattostr(input); 
    if (input <= 0) then begin
      Writeln('Вторая часть не натуральная');
    end else if (element in C) then begin
      Writeln('Элемент уже в множестве');
    end else begin
      Include(C, element);
      i := i + 1;
    end;
  end;
  //
  Writeln('Введите мощность D (лат. буквы):');
  powerCheck();
  Writeln('Введите элементы :');
  power:= input;
  i := 0;
  while i < power do begin
    readln(&tempChar);
    element:= tempChar;
    if ((Ord(tempChar) >= 65) and (Ord(tempChar) <= 90)) or ((Ord(tempChar) >= 97) and (Ord(tempChar) <= 122)) then begin
      if (element in D) then begin
        Writeln('Элемент уже в множестве');
      end else begin
        Include(D, element);
        i := i + 1;
      end;
    end else begin
      Writeln('Неправильный ввод, повторить попытку? (1 - да, 0 - нет)');
      Readln(&tempInt);
      if tempInt = 0 then i := power;
    end;
  end;
  //
  Writeln('Введите мощность E (русс. буквы)::');
  powerCheck();
  Writeln('Введите элементы :');
  power:= input;
  i := 0;
  while i < power do begin
    readln(&tempChar);
    element:= tempChar;
    if (Ord(tempChar) >= 1040) and (Ord(tempChar) <= 1103) then begin
      if (element in E) then begin
        Writeln('Элемент уже в множестве');
      end else begin
        Include(E, element);
        i := i + 1;
      end;
    end else begin
      Writeln('Неправильный ввод, повторить попытку? (1 - да, 0 - нет)');
      Readln(&tempInt);
      if tempInt = 0 then i := power;
    end;
  end;
  Writeln('A (Натуральные числа) = ', A);
  Writeln('B (Действительные числа) = ', B);
  Writeln('C (Рациональные числа) = ', C);
  Writeln('D (Лат. буквы) = ', D);
  Writeln('E (Русс. буквы) = ', E);
   
  X := A * B * C;
  Y := E - D;
  K := (X + Y) - (X * Y);
  writeln('');
  Writeln('X (Пересечение A,B,C) = ', X);
  Writeln('Y (Разность E/D) = ', Y);
  Writeln('K (Симметричная разность X△K) = ', K);
  Writeln('Мощность K = ', K.count);
end.