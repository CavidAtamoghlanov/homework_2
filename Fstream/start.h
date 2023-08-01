#pragma once

void start()
{
	int count_tc = 1;
	Teacher** teachers = new Teacher*[count_tc];
	teachers[0] = new Teacher("Cavid", "Atamoglanov", "j.atamoghlanov98@gmail.com", 25, 3500, "cavid98");
	int indexx = 0;

	string password_tc, name_tc;
	while (true) // teacherin axtarishi
	{
		cout << "Enter your 'name': ";
		cin >> name_tc;
		cout << "Enter your 'password': ";
		cin >> password_tc;
		bool isCheck = true;
		for (size_t i = 0; i < count_tc; i++)
		{
			if (teachers[i]->getName() == name_tc && teachers[i]->getPassword() == password_tc)
			{
				cout << "Welcome " << name_tc << endl;
				isCheck = false;
				indexx = i;
				break;
			}
		}
		if (isCheck)
			throw exception("teacher was not found"); // tapilmazsa error atir tapilsa indexse gore yenisini yaradib beraber edirik ki rahat isledek
		else
			break;
	}

	//Student* ibrahim = new Student("Ibrahim", "Alizada", "lizad2ibrahim@gmail.com", 16, 11, "22bcd");

	Teacher* cavid = teachers[indexx];
	Teacher** n_teachers = new Teacher * [count_tc + 1];
	for (size_t i = 0; i < count_tc; i++)
		n_teachers[i] = teachers[i];
	n_teachers[count_tc] = cavid;
	count_tc++;

	if (teachers != NULL)
		delete[] teachers;
	teachers = n_teachers;


	//teachers[indexx]->createStudent(ibrahim);

	string name, surname, email, group;
	ushort age;
	float avg;
	ifstream file("allStudents.txt", ios::in);
	if (file.is_open())
	{
		file >> name;
		while (!file.eof() && name.length() >= 1)
		{
			file >> surname;
			file >> email;
			file >> age;
			cin.ignore();
			file >> avg;
			cin.ignore();
			getline(file, group);

			Student* student = new Student(name, surname, email, age, avg, group);
			cavid->createStudent(student);
		}
	}
	file.close();

	cout << "[1] => Show AllStudent\n";
	cout << "[2] => Show same Group Students\n";
	cout << "[3] => Create Student\n";
	cout << "[4] => Delete student\n";
	cout << "[5] => Save\n";
	cout << "[0] => Exit\n";
	int choise;
	while (true)
	{
		cout << "Enter your 'choise': ";
		cin >> choise;
		if (choise == 1)
		{
			for (size_t i = 0; i < cavid->getSize(); i++)
				cavid->getStudents()[i]->show();
		}
		else if (choise == 2)
		{
			string gp_n;
			cout << "Enter group name: ";
			cin >> gp_n;
			cavid->showSameGroupSTs(gp_n);
		}
		else if (choise == 3)
		{
			string name, surname, email, group;
			float avg;
			ushort age;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter surname: ";
			cin >> surname;
			cout << "Enter email: ";
			cin >> email;
			cout << "Enter group: ";
			cin >> group;
			cout << "Enter age: ";
			cin >> age;
			cin.ignore();
			cout << "Enter avg: ";
			cin >> avg;
			cin.ignore();
			Student* create_st = new Student(name, surname, email, age, avg, group);
			cavid->createStudent(create_st);
		}
		else if (choise == 4)
		{
			string delete_email_st;
			cout << "Enter deleted student of email: ";
			cin >> delete_email_st;
			cavid->deleteStudent(delete_email_st);
		}
		else if (choise == 5)
		{
			ofstream file("allStudents.txt", ios::out);
			if (file.is_open())
			{
				for (size_t i = 0; i < cavid->getSize(); i++)
					file << cavid->getStudents()[i]->showFile();
			}
			file.close();
		}
		else if (choise == 0)
		{
			cout << "BYE-BYE." << endl;
			break;
		}
		else
			throw exception("wrong choise");
	}
}