import postgresql

class database:
    def __init__(self):
        self._connection = None
        self._url = 'pq://py_reader:lab1pass@localhost:5432/lab1_db'

    def openConnection(self):
        try:
            self._connection = postgresql.open(self._url)
            print("Connected successfully")
            return True
        except Exception as e:
            print(f"Connection error: {e}")
            self._connection = None
            return False
            
    def closeConnection(self):
        if self._connection is not None:
            try:
                self._connection.close()
                print("Connection closed")
            except Exception as e:
                print(f"Error closing connection: {e}")
            finally:
                self._connection = None
        else:
            print("Connection is closed or was never opened")

        
    def getTable(self):
        if self._connection is not None:
            try:
                print(f"Table: students")
                return self._connection.query(f"SELECT * FROM lab1_schema.students")
            except Exception as e:
                print(f"Error: {e}")
                return None
        else:
            print("Connection not active")
    
    def insertStudent(self, first_name, last_name, age, faculty_name) -> int:
        if self._connection is not None:
            try:
                duplicatesSQL = self._connection.prepare("SELECT COUNT(*) FROM lab1_schema.students WHERE first_name = $1 AND last_name = $2 AND age = $3 AND faculty_name = $4") 
                dups = duplicatesSQL(first_name, last_name, int(age), faculty_name)
                if dups is not None and int(dups[0][0]) > 0:
                    print("Student already exists in students")
                    return -1

                insertSQL = self._connection.prepare("SELECT lab1_schema.insert_student($1, $2, $3, $4)")
                insertSQL(first_name, last_name, int(age), faculty_name)
                print(f"Successfully added student: {first_name} {last_name}, {age}, {faculty_name}")

                return 0

            except Exception as e:
                print(f"Error inserting: {e}")
                return 1
        else:
            print("Connection not active (insertStudent)")
            return 1
        
    def deleteStudent(self, ID) -> bool:
        if self._connection is not None:
            try:

                deleteSQL = self._connection.prepare("SELECT lab1_schema.delete_student($1)") 
                isDeleted = deleteSQL(int(ID))
                if not isDeleted:
                    print("Error, student with this ID does not exist")
                    return False

                print(f"Successfully deleted student: ID: {ID}")

                return True

            except Exception as e:
                print(f"Error deleting: {e}")
                return False
        else:
            print("Connection not active (deleteStudent)")
            return False

    def filterTable(self, first_name, last_name, age, faculty):
        if self._connection is not None:
            try:
                base_query = "SELECT * FROM lab1_schema.students WHERE 1=1"
                params = []
                param_count = 0
                
                if first_name:
                    param_count += 1
                    base_query += f" AND first_name ILIKE ${param_count}"
                    params.append(f"%{first_name}%")
                    
                if last_name:
                    param_count += 1
                    base_query += f" AND last_name ILIKE ${param_count}"
                    params.append(f"%{last_name}%")
                    
                if age:
                    if age.isdigit():
                        param_count += 1
                        base_query += f" AND age = ${param_count}"
                        params.append(int(age))
                    else:
                        return self.getTable()
                        
                if faculty:
                    param_count += 1
                    base_query += f" AND faculty_name ILIKE ${param_count}"
                    params.append(f"%{faculty}%")
                
                print(f"Executing query: {base_query} with params: {params}")
                result = self._connection.query(base_query, *params)
                print(result)
                return result
                
            except Exception as e:
                print(f"Error filtering table: {e}")
                return self.getTable()
        else:
            print("Connection not active")
            return self.getTable()      