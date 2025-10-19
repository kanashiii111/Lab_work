using System.Diagnostics;
using System.Windows.Forms;

namespace lab4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            DB.FirstLoad(dataGridView1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string name = textBox1.Text.Trim();
            string lastName = textBox2.Text.Trim();
            string ageText = textBox3.Text.Trim();
            string faculty = comboBox1.Text.Trim();

            // Проверка обязательных полей
            if (string.IsNullOrEmpty(name) || string.IsNullOrEmpty(lastName) || string.IsNullOrEmpty(faculty))
            {
                MessageBox.Show("Заполните все обязательные поля", "Ошибка");
                return;
            }

            // Проверка возраста
            if (!int.TryParse(ageText, out int age))
            {
                MessageBox.Show("Возраст должен быть числом", "Ошибка");
                textBox3.Focus();
                return;
            }

            // Дополнительная проверка диапазона возраста

            bool op = DB.Add(dataGridView1, name, lastName, age, faculty);
            DB.FirstLoad(dataGridView1);
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            // Проверяем, что есть текущая ячейка
            if (dataGridView1.CurrentCell == null)
            {
                MessageBox.Show("Выберите студента для удаления", "Информация");
                return;
            }

            // Получаем индекс строки через CurrentCell
            int rowIndex = dataGridView1.CurrentCell.RowIndex;
            DataGridViewRow selectedRow = dataGridView1.Rows[rowIndex];

            string? studentId = selectedRow.Cells[0].Value?.ToString();
            string studentName = $"{selectedRow.Cells[1].Value} {selectedRow.Cells[2].Value}";

            // Подтверждение удаления
            DialogResult result = MessageBox.Show(
                $"Вы уверены, что хотите удалить студента:\n{studentName} (ID: {studentId})?",
                "Подтверждение удаления",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (result == DialogResult.Yes)
            {
                // Вызываем функцию удаления
                bool success = DB.Delete(Convert.ToInt64(studentId));

                if (success)
                {
                    MessageBox.Show("Студент успешно удален", "Успех");

                    // Удаляем строку из DataGridView
                    // dataGridView1.Rows.RemoveAt(rowIndex);
                    DB.FirstLoad(dataGridView1);
                }
                else
                {
                    MessageBox.Show("Не удалось удалить студента", "Ошибка");
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string name = textBox6.Text.Trim();
            string lastName = textBox5.Text.Trim();
            string age = textBox4.Text.Trim(); // Оставляем как строку
            string faculty = comboBox2.Text.Trim();
            DB.Filter(dataGridView1, name, lastName, age, faculty);
        }
    }
}
