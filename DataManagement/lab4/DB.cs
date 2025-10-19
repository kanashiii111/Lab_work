using Npgsql;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
//using System.Diagnostics;

public class DB
{
    public static string[,] Read()
    {
        string connectionString = "Server=127.0.0.1; Port=5432; User Id=py_reader; Password=lab1pass; Database=lab1_db";

        try
        {
            using (var conn = new NpgsqlConnection(connectionString))
            {
                conn.Open();

                // Убедитесь, что запрос включает faculty_id
                string sql = "SELECT id, first_name, last_name, age, faculty_name, faculty_id FROM lab1_schema.students";

                using (var com = new NpgsqlCommand(sql, conn))
                using (var reader = com.ExecuteReader())
                {
                    // Временное хранилище
                    var dataList = new List<string[]>();

                    while (reader.Read())
                    {
                        string[] row = new string[6]; // 6 колонок
                        row[0] = reader.GetInt64(0).ToString(); // id
                        row[1] = reader.GetString(1); // first_name
                        row[2] = reader.GetString(2); // last_name
                        row[3] = reader.GetInt32(3).ToString(); // age
                        row[4] = reader.GetString(4); // faculty_name
                        row[5] = reader.GetInt32(5).ToString(); // faculty_id - ВАЖНО!
                        dataList.Add(row);
                    }

                    // Конвертируем в двумерный массив
                    string[,] result = new string[dataList.Count, 6];
                    for (int i = 0; i < dataList.Count; i++)
                    {
                        for (int j = 0; j < 6; j++)
                        {
                            result[i, j] = dataList[i][j];
                        }
                    }
                    return result;
                }
            }
        }
        catch (Exception E)
        {
            Console.WriteLine("Database error: " + E.Message);
            return new string[0, 6];
        }
    }
    public static void FirstLoad(DataGridView datagridview)
    {
        string[,] data = Read();

        // Очищаем существующие колонки и строки
        datagridview.Columns.Clear();
        datagridview.Rows.Clear();
        datagridview.AutoGenerateColumns = false;

        // Если нет данных
        if (data.GetLength(0) == 0)
        {
            MessageBox.Show("Нет данных для отображения");
            return;
        }

        try
        {
            // Создаем колонки
            string[] columnHeaders = { "ID", "Имя", "Фамилия", "Возраст", "Факультет", "ID Факультета" };

            for (int i = 0; i < data.GetLength(1); i++)
            {
                DataGridViewColumn column;

                // Для числовых колонок используем правильный тип
                if (i == 0 || i == 3 || i == 5) // ID, Age, Faculty_ID - числовые
                {
                    column = new DataGridViewTextBoxColumn();
                }
                else // Остальные - текстовые
                {
                    column = new DataGridViewTextBoxColumn();
                }

                column.HeaderText = i < columnHeaders.Length ? columnHeaders[i] : $"Column {i + 1}";
                column.Name = $"Column{i}";
                datagridview.Columns.Add(column);
            }

            // Устанавливаем количество строк
            datagridview.RowCount = data.GetLength(0);

            // Заполняем данными
            for (int i = 0; i < data.GetLength(0); i++)
            {
                for (int j = 0; j < data.GetLength(1); j++)
                {
                    datagridview.Rows[i].Cells[j].Value = data[i, j];
                }
            }

            // Автоподбор ширины колонок
            // Растягиваем колонки на всю ширину
            datagridview.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;

            // Растягиваем строки на всю высоту
            datagridview.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;

            // Чтобы DataGridView занимал всю доступную область
            //datagridview.Dock = DockStyle.Fill;
        }
        catch (Exception ex)
        {
            MessageBox.Show($"Ошибка при загрузке данных: {ex.Message}", "Ошибка");
        }
    }

    public static void Load(DataGridView dataGridView, string[,] data)
    {
        dataGridView.AllowUserToAddRows = false;

        dataGridView.Rows.Clear();
        dataGridView.Columns.Clear();

        // Создаем колонки
        string[] headers = { "ID", "Имя", "Фамилия", "Возраст", "Факультет", "ID Факультета" };
        foreach (string header in headers)
        {
            dataGridView.Columns.Add(header, header);
        }

        // Заполняем данными
        for (int i = 0; i < data.GetLength(0); i++)
        {
            int rowIndex = dataGridView.Rows.Add();
            for (int j = 0; j < data.GetLength(1); j++)
            {
                dataGridView.Rows[rowIndex].Cells[j].Value = data[i, j];
            }
        }

        // Настраиваем внешний вид
        dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
        dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
    }
    public static bool Add(DataGridView dataGridView, string name, string lastName, int age, string faculty)
    {
        string connectionString = "Host=localhost; User Id=py_reader; Password=lab1pass; Database=lab1_db";

        NpgsqlConnection conn = null;
        NpgsqlCommand com = null;

        try
        {
            conn = new NpgsqlConnection(connectionString);
            conn.Open();

            string checkDuplicateSql = @"
            SELECT COUNT(*) 
            FROM lab1_schema.students 
            WHERE first_name = @p1 
            AND last_name = @p2 
            AND age = @p3 
            AND faculty_name = @p4";

            using (var checkCmd = new NpgsqlCommand(checkDuplicateSql, conn))
            {
                checkCmd.Parameters.AddWithValue("@p1", name);
                checkCmd.Parameters.AddWithValue("@p2", lastName);
                checkCmd.Parameters.AddWithValue("@p3", age);
                checkCmd.Parameters.AddWithValue("@p4", faculty);

                long duplicateCount = (long)checkCmd.ExecuteScalar();

                if (duplicateCount > 0)
                {
                    MessageBox.Show($"Студент {name} {lastName} уже существует в {faculty}", "Error");
                    return false;
                }
            }

            com = new NpgsqlCommand("SELECT lab1_schema.insert_student(@p1, @p2, @p3, @p4)", conn);
            var a = new NpgsqlParameter("@p1", NpgsqlTypes.NpgsqlDbType.Varchar);
            var b = new NpgsqlParameter("@p2", NpgsqlTypes.NpgsqlDbType.Varchar);
            var c = new NpgsqlParameter("@p3", NpgsqlTypes.NpgsqlDbType.Integer);
            var d = new NpgsqlParameter("@p4", NpgsqlTypes.NpgsqlDbType.Varchar);

            a.Value = name;
            b.Value = lastName;
            c.Value = age;
            d.Value = faculty;
            com.Parameters.Add(a);
            com.Parameters.Add(b);
            com.Parameters.Add(c);
            com.Parameters.Add(d);
            com.ExecuteNonQuery();

            return true;
        }
        catch (Exception E)
        {
            MessageBox.Show($"Ошибка при добавлении студента: {E.Message}");
            return false;
        }
        finally
        {
            conn?.Close();
        }
    }
    public static bool Delete(long Id)
    {
        string connectionString = "Host=localhost; User Id=py_reader; Password=lab1pass; Database=lab1_db";

        try
        {
            using (var conn = new NpgsqlConnection(connectionString))
            {
                conn.Open();

                using (var com = new NpgsqlCommand("SELECT lab1_schema.delete_student(@p_student_id)", conn))
                {
                    com.Parameters.AddWithValue("@p_student_id", Id);

                    com.ExecuteNonQuery();
                    return true;
                }
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show($"Error deleting student: {ex.Message}", "Error");
            return false;
        }
    }
    public static void Filter(DataGridView dataGridView, string firstName = "", string lastName = "",
                         string age = "", string faculty = "")
    {
        string[,] data = DB.Read();
        string[,] filteredData = GetFilteredData(firstName, lastName, age, faculty);

        if (filteredData.GetLength(0) == 0)
        {
            string msg = "Студенты не найдены";
            MessageBox.Show(msg, "Информация", MessageBoxButtons.OK);
            Load(dataGridView, data);
            return;
        }

        Load(dataGridView, filteredData);
    }
    private static string[,] GetFilteredData(string firstName = "", string lastName = "",
                                       string age = "", string faculty = "")
    {
        string connectionString = "Host = localhost; User Id=py_reader; Password=lab1pass; Database=lab1_db";

        try
        {
            using (var conn = new NpgsqlConnection(connectionString))
            {
                conn.Open();

                string sql = @"SELECT id, first_name, last_name, age, faculty_name, faculty_id 
                      FROM lab1_schema.students";

                var parameters = new List<NpgsqlParameter>();
                var conditions = new List<string>();

                // Фильтр по имени
                if (!string.IsNullOrEmpty(firstName))
                {
                    conditions.Add("first_name ILIKE @firstName");
                    parameters.Add(new NpgsqlParameter("@firstName", $"%{firstName}%"));
                }

                // Фильтр по фамилии
                if (!string.IsNullOrEmpty(lastName))
                {
                    conditions.Add("last_name ILIKE @lastName");
                    parameters.Add(new NpgsqlParameter("@lastName", $"%{lastName}%"));
                }

                // Фильтр по возрасту
                if (!string.IsNullOrEmpty(age))
                {
                    if (int.TryParse(age, out int ageValue))
                    {
                        conditions.Add("age = @age");
                        parameters.Add(new NpgsqlParameter("@age", ageValue));
                    }
                }

                // Фильтр по факультету
                if (!string.IsNullOrEmpty(faculty))
                {
                    conditions.Add("faculty_name = @faculty");
                    parameters.Add(new NpgsqlParameter("@faculty", faculty));
                }

                // Добавляем условия WHERE если есть фильтры
                if (conditions.Count > 0)
                {
                    sql += " WHERE " + string.Join(" AND ", conditions);
                }

                // Сортировка по ID
                sql += " ORDER BY id";

                using (var com = new NpgsqlCommand(sql, conn))
                {
                    foreach (var param in parameters)
                    {
                        com.Parameters.Add(param);
                    }

                    using (var reader = com.ExecuteReader())
                    {
                        var dataList = new List<string[]>();

                        while (reader.Read())
                        {
                            string[] row = new string[6];
                            row[0] = reader.GetInt64(0).ToString(); // id
                            row[1] = reader.GetString(1); // first_name
                            row[2] = reader.GetString(2); // last_name
                            row[3] = reader.GetInt32(3).ToString(); // age
                            row[4] = reader.GetString(4); // faculty_name
                            row[5] = reader.GetInt32(5).ToString(); // faculty_id
                            dataList.Add(row);
                        }

                        string[,] result = new string[dataList.Count, 6];
                        for (int i = 0; i < dataList.Count; i++)
                        {
                            for (int j = 0; j < 6; j++)
                            {
                                result[i, j] = dataList[i][j];
                            }
                        }
                        return result;
                    }
                }
            }
        }
        catch (Exception E)
        {
            Console.WriteLine("Database error: " + E.Message);
            return new string[0, 6];
        }
    }
}