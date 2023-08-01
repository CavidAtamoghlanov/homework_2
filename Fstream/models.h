#pragma once
bool endswith(string str, string end, int index)
{
	string new_str;
	for (int i = index; i < str.length(); i++)
		new_str += str[i];

	if (new_str == end)
		return true;
	else
		return false;
}

class Person
{
private:
	string _name;
	string _surname;
	string _email;
	ushort _age;
public:
	Person() = delete;
	Person(string name, string surname, string email, ushort age)
	{
		setName(name);
		setSurname(surname);
		setEmail(email);
		setAge(age);
	}

	inline string getName() const { return _name; }
	inline string getSurname() const { return _surname; }
	inline string getEmail() const { return _email; }
	inline ushort getAge() const { return _age; }

	void setName(string name)
	{
		if (name.length() >= 3)
			_name = name;
		else
			throw exception("Name is wrong");
	}
	void setSurname(string surname)
	{
		if (surname.length() >= 5)
			_surname = surname;
		else
			throw exception("Surname is wrong");
	}
	void setEmail(string email)
	{
		if (email.length() >= 5 && endswith(email, "@gmail.com", email.length() - 10) || email == "Null")
			_email = email;
		else
			throw exception("error in email");
	}
	void setAge(ushort age)
	{
		if (age >= 1 && age <= 70)
			_age = age;
		else
			throw exception("wrong age (1-70)");
	}

	virtual void show()
	{
		cout << "Name: " << _name << "\nSurname: " << _surname << "\nEmail: " << _email << "\nAge: " << _age << endl;
	}
	virtual string showFile()
	{
		return (_name + " " + _surname + " " + _email + " " + to_string(_age) + " ");
	}

	virtual ~Person() = 0 {};
};


class Student : public Person
{
	float _avg;
	string _group;
public:
	Student() = delete;
	Student(string name, string surname, string email, ushort age, float avg, string group) : Person(name, surname, email, age)
	{
		setAvg(avg);
		setGroup(group);
	}

	inline float getAvg() const { return _avg; }
	inline string getGroup() const { return _group; }

	void setAvg(float avg)
	{
		if (avg >= 1 && avg <= 12)
			_avg = avg;
		else
			throw exception("wrong avg (1-12)");
	}
	void setGroup(string group)
	{
		if (group.length() >= 3)
			_group = group;
		else
			throw exception("wrong group name");
	}

	void show() override
	{
		cout << "--Student Info--" << endl;
		Person::show();
		cout << "Average: " << _avg << "\nGroup name: " << _group << endl;
	}
	string showFile() override
	{
		string data;
		data = Person::showFile() + to_string(_avg) + " " + _group + "\n";
		return data;
	}
};

class Teacher : public Person
{
private:
	string _password;
	float _salary;
	Student** studentsArr = NULL;
	int size = 0;
public:
	Teacher() = delete;
	Teacher(string name, string surname, string email, ushort age, float salary, string password) : Person(name, surname, email, age)
	{
		setSalary(salary);
		setPassword(password);
	}
	Teacher(const Teacher& tc) : Person(tc.getName(), tc.getSurname(), tc.getEmail(), tc.getAge())
	{
		setSalary(tc.getSalary());
		setPassword(tc.getPassword());
	}

	inline float getSalary() const { return _salary; }
	inline string getPassword() const { return _password; }
	inline int getSize() const { return size; }
	inline Student** getStudents() const { return studentsArr; }

	void setSalary(float salary)
	{
		if (salary >= 500)
			_salary = salary;
		else
			throw exception("Wrong Teacher Salary(min. 500)");
	}
	void setPassword(string password)
	{
		if (password != _password && password.length() >= 5)
			_password = password;
		else
			throw exception("either the codes are the same or the code is too short");
	}

	void createStudent(Student* st)
	{
		Student** new_sts = new Student * [size + 1];

		for (size_t i = 0; i < size; i++)
			new_sts[i] = studentsArr[i];
		new_sts[size] = st;
		delete[] studentsArr;
		studentsArr = new_sts;
		size++;
	}
	void deleteStudent(string email)
	{
		Student** new_sts = new Student * [size - 1];

		int index = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (studentsArr[i]->getEmail() == email)
			{
				index = i;
				break;
			}
		}
		for (size_t i = 0; i < index; i++)
			new_sts[i] = studentsArr[i];
		for (size_t i = index; i < size; i++)
			new_sts[i++] = studentsArr[i];
		delete[] studentsArr;
		studentsArr = new_sts;
		size--;
	}
	void showSameGroupSTs(string group)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (studentsArr[i]->getGroup() == group)
				studentsArr[i]->show();
		}
	}

	void show() override
	{
		cout << "-- Teacher Info --" << endl;
		Person::show();
		cout << "Salary: " << _salary << endl;
	}
	string showFile() override
	{
		string data;
		data = Person::showFile() + to_string(_salary) + "\n";
		return data;
	}
};