import tkinter as tk
from tkinter import ttk
from tkinter.messagebox import showerror, showwarning, showinfo, askyesno
import database

WIDTH = 1200
HEIGHT = 400

FILTER_HEIGHT = 248
ADD_HEIGHT = 248 + 100
REMOVE_HEIGHT = 248 + 50

class App:
    def __init__(self):
        ## DB

        self.db = database.database()
        
        ## WINDOW

        self.window = tk.Tk()
        self.window.geometry("1200x400")
        self.window.resizable(False, False)
        self.window.title("lab5")
        
        ## TABLE
        self.table = ttk.Treeview(columns=("name", "lastName", "age", "faculty", "facultyId"))
        self.loadTable(self.table)
        self.loadButtons()
        self.loadFilterBoxes()
        self.loadAddBoxes()
        self.loadLabels()
        
        self.window.mainloop()
        
    def loadTable(self, table, data = None):
        if data is not None:
            self.dbTable = data
        else:
            self.dbTable = self.db_getTable()
        self.table = table
        self.table.delete(*self.table.get_children())
        self.tableColumns = [["#0", "ID"], ["name", "Имя"], ["lastName", "Фамилия"], ["age", "Возраст"], ["faculty", "Факультет"], ["facultyId", "ID Факультета"]]

        for column, columnText in self.tableColumns:
            self.table.heading(column, text=columnText)
        for row in self.dbTable:
            self.table.insert(
                "",
                tk.END,
                text=row[0],
                values=(row[1], row[2], row[3], row[4], row[5])
            )
        self.table.pack(anchor="n")

    def addButtonClick(self):
        self.name = self.nameAdd.get().strip()
        self.lastName = self.lastNameAdd.get().strip()
        self.age = self.ageAdd.get().strip()
        self.faculty = self.facultyAdd.get().strip()
        if not self.name or not self.lastName or not self.faculty:
            showwarning(title="Предупреждение", message="Заполните все обязательные поля")
            return
        if not (self.age.isdigit()):
            showwarning(title="Предупреждение", message="Возраст должен быть целым положительным числом")
            return
            
        self.db_insert(self.name, self.lastName, self.age, self.faculty)
        self.loadTable(self.table)

    def removeButtonClick(self):
        self.selectedRows = self.table.selection()
        if self.selectedRows:
            ids = []
            students_list = []
            for row in self.selectedRows:
                item_data = self.table.item(row)
                first_name = item_data.get('values')[0]
                last_name = item_data.get('values')[1]
                ids.append(item_data.get('text', []))
                students_list.append(f"{first_name} {last_name}")

            if (len(ids) > 1):
                students_names = ", ".join(students_list)
                result = askyesno(title="Подтверждение операции", message=f"Вы уверены, что хотите удалить следующих студентов:\n{students_names}?")
            else:
                result = askyesno(title="Подтверждение операции", message=f"Вы уверены, что хотите удалить студента: {students_list[0]}?")
            
            if result: 
                self.db_delete(ids)
                if (len(ids) > 1):
                    showinfo(title="Результат", message="Студенты успешно удалены")
                else:
                    showinfo(title="Результат", message="Студент успешно удален")
            else: 
                if (len(ids) > 1):
                    showinfo(title="Результат", message="Не удалось удалить студентов")
                else:
                    showinfo(title="Результат", message="Не удалось удалить студента")

            self.loadTable(self.table)
        else:
            showwarning(title="Предупреждение", message="Выберите студента/студентов для удаления")

    def filterButtonClick(self):
        self.name = self.nameFilter.get().strip()
        self.lastName = self.lastNameFilter.get().strip()
        self.age = self.ageFilter.get().strip()
        self.faculty = self.facultyFilter.get().strip()
        
        filteredData = self.db_filteredData(self.name, self.lastName, self.age, self.faculty)
        if len(filteredData) == 0 or filteredData is None:
            self.loadTable(self.table)
            showwarning(title="Предупреждение", message="Студенты не найдены")
            return
        self.loadTable(self.table,filteredData)  

    def loadButtons(self):
        ## FILTER BUTTON
        
        self.filterButton = ttk.Button(text="Сохранить", width=30, command=self.filterButtonClick)
        self.filterButton.place(x=1010, y=FILTER_HEIGHT-2)

        ## REMOVE BUTTON
        
        self.removeButton = ttk.Button(text="Удалить выбранную строку", width=30, command=self.removeButtonClick)
        self.removeButton.place(x=1010, y=REMOVE_HEIGHT),

        ## ADD BUTTON
        
        self.addButton = ttk.Button(text="Добавить запись", width=30, command=self.addButtonClick)
        self.addButton.place(x=1010, y=ADD_HEIGHT-2)
        
    def loadFilterBoxes(self):
        
        self.nameFilter = ttk.Entry(width=30)
        self.nameFilter.place(x=200, y=FILTER_HEIGHT)
    
        self.lastNameFilter = ttk.Entry(width=30)
        self.lastNameFilter.place(x=400, y=FILTER_HEIGHT)

        self.ageFilter = ttk.Entry(width=30)
        self.ageFilter.place(x=600, y=FILTER_HEIGHT)

        self.facultyFilter = ttk.Combobox(values=("ФАВТ", "ФКиФМН", "ФПиП", "ФФКиС"), width=30)
        self.facultyFilter.place(x=800, y=FILTER_HEIGHT)
        
    def loadAddBoxes(self):
        
        self.nameAdd = ttk.Entry(width=30)
        self.nameAdd.place(x=200, y=ADD_HEIGHT)
    
        self.lastNameAdd = ttk.Entry(width=30)
        self.lastNameAdd.place(x=400, y=ADD_HEIGHT)

        self.ageAdd = ttk.Entry(width=30)
        self.ageAdd.place(x=600, y=ADD_HEIGHT)

        self.facultyAdd = ttk.Combobox(values=("ФАВТ", "ФКиФМН", "ФПиП", "ФФКиС"), width=30)
        self.facultyAdd.place(x=800, y=ADD_HEIGHT)
        
    def loadLabels(self):
        
        self.nameAddLabel = ttk.Label(text="Имя", width=30)
        self.nameAddLabel.place(x=200, y=ADD_HEIGHT-20)
    
        self.lastNameAddLabel = ttk.Label(text="Фамилия", width=30)
        self.lastNameAddLabel.place(x=400, y=ADD_HEIGHT-20)

        self.ageAddLabel = ttk.Label(text="Возраст", width=30)
        self.ageAddLabel.place(x=600, y=ADD_HEIGHT-20)

        self.facultyAddLabel = ttk.Label(text="Факультет", width=30)
        self.facultyAddLabel.place(x=800, y=ADD_HEIGHT-20)
        
        self.infoAddLabel = ttk.Label(text="Добавление записи", width=20)
        self.infoAddLabel.place(x=50, y=ADD_HEIGHT)



        self.nameFilterLabel = ttk.Label(text="Имя", width=30)
        self.nameFilterLabel.place(x=200, y=FILTER_HEIGHT-20)
    
        self.lastNameFilterLabel = ttk.Label(text="Фамилия", width=30)
        self.lastNameFilterLabel.place(x=400, y=FILTER_HEIGHT-20)

        self.ageFilterLabel = ttk.Label(text="Возраст", width=30)
        self.ageFilterLabel.place(x=600, y=FILTER_HEIGHT-20)

        self.facultyFilterLabel = ttk.Label(text="Факультет", width=30)
        self.facultyFilterLabel.place(x=800, y=FILTER_HEIGHT-20)

        self.infoFilterLabel = ttk.Label(text="Фильтр", width=20)
        self.infoFilterLabel.place(x=50, y=FILTER_HEIGHT)

    def db_getTable(self):
        self.db.openConnection()
        self.dbTable = self.db.getTable()
        self.db.closeConnection()
        return self.dbTable
    
    def db_insert(self, first_name, last_name, age, faculty):
        self.db.openConnection()
        if (self.db.insertStudent(first_name, last_name, age, faculty)) == -1:
            showwarning(title="Предупреждение", message="Студент уже существует")
        self.db.closeConnection()
        
    def db_delete(self, ID):
        self.db.openConnection()
        for id in ID:
            self.db.deleteStudent(id)
        self.db.closeConnection()
    
    def db_filteredData(self, first_name="", last_name="", age="", faculty=""):
        self.db.openConnection()
        self.dbFilteredTable = self.db.filterTable(first_name, last_name, age, faculty)
        self.db.closeConnection()
        return self.dbFilteredTable
    
if __name__ == "__main__":
    app = App()