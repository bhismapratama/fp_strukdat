#include <iostream>
#include <string>

using namespace std;

const int MAX_ADMINS = 3;  // kasih batas maksimal admin
const int MAX_USERS = 100; // kasih batas maksimal user

// definisi class
class Display
{
public:
    virtual ~Display() = default;
    virtual void notification() const = 0;
};

// definisi class user
class User : public Display
{
protected:
    string username;
    string password;

public:
    User(const string &username, const string &password) : username(username), password(password) {}

    void notification() const override
    {
        cout << "User: " << username << endl;
    }
};

// definisi class admin
class Admin : public User
{
public:
    Admin(const string &username, const string &password) : User(username, password) {}

    void notification() const override
    {
        cout << "Admin: " << username << endl;
    }
};

// definisi class dashboard
class Dashboard
{
private:
    User **users;                      // array dinamis simpan User dan Admin
    int userCount;                     // jumah user yang ditambah
    string *userActivities[MAX_USERS]; // array dinamis simpan kegiatan user

public:
    Dashboard() : users(new User *[MAX_ADMINS]), userCount(0)
    {
        for (int i = 0; i < MAX_USERS; ++i)
        {
            userActivities[i] = nullptr;
        }
    }

    ~Dashboard()
    {
        // dealokasi user
        for (int i = 0; i < userCount; ++i)
        {
            delete users[i];
        }
        delete[] users;

        // dealokasi activity
        for (int i = 0; i < MAX_USERS; ++i)
        {
            delete userActivities[i];
        }
    }

    bool isAdminLimitReached() const
    {
        return userCount >= MAX_ADMINS;
    }

    void addUser(User *user)
    {
        if (userCount < MAX_ADMINS + MAX_USERS)
        {
            users[userCount++] = user;
        }
        else
        {
            cout << "dah penuh" << endl;
            delete user;// hapus user yang tidak ditambah di array
        }
    }

    void displayUsers() const
    {
        cout << "=== Users ===" << endl;
        for (int i = 0; i < userCount; ++i)
        {
            users[i]->notification();
        }
        cout << "=============" << endl;
    }

    void addActivity(const string &username, const string &activity)
    {
        for (int i = 0; i < MAX_USERS; ++i)
        {
            if (userActivities[i] == nullptr)
            {
                userActivities[i] = new string(activity);
                cout << "kegiatan ditambahkan" << endl;
                return;
            }
        }

        cout << "dah penuhh" << endl;
    }

    void displayUserActivities() const
    {
        cout << "=== Aktivitas Users ===" << endl;
        for (int i = 0; i < MAX_USERS; ++i)
        {
            if (userActivities[i] != nullptr)
            {
                cout << *(userActivities[i]) << endl;
            }
        }
        cout << "========================" << endl;
    }
};

int main()
{
    Dashboard dashboard;

    while (true)
    {
        cout << "MAUNYA SI FP" << endl;
        cout << "1. login sebagai admin" << endl;
        cout << "2. login sebagai user" << endl;
        cout << "3. tampilkan dashboard" << endl;
        cout << "0. keluar" << endl;

        int choice;
        cout << "pilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string username, password;
            cout << "masukkan username admin: ";
            cin >> username;
            cout << "masukkan password admin: ";
            cin >> password;

            // cek pokona admin cuma 3
            if (dashboard.isAdminLimitReached())
            {
                cout << "dah penuh" << endl;
            }
            else
            {
                Admin *admin = new Admin(username, password);
                dashboard.addUser(admin);
                cout << "admin " << username <<" berhasil ditambahkan" << endl;
            }
            break;
        }

        case 2:
        {
            string username, password;
            cout << "masukkan username user: ";
            cin >> username;
            cout << "masukkan password user: ";
            cin >> password;

            User *user = new User(username, password);
            dashboard.addUser(user);
            cout << "User " << username <<" berhasil ditambahkan" << endl;
            break;
        }

        case 3:
        {
            dashboard.displayUsers();

            // pilihan di dashboard
            while (true)
            {
                cout << "Pilihan Dashboard:" << endl;
                cout << "1. tambah user" << endl;
                cout << "2. tambah kegiatan user" << endl;
                cout << "3. tampilkan kegiatan user" << endl;
                cout << "0. keluar dari dashboard" << endl;

                int dashboardChoice;
                cout << "pilihan: ";
                cin >> dashboardChoice;

                if (dashboardChoice == 0)
                {
                    break; // keluar dashboard
                }

                switch (dashboardChoice)
                {
                case 1:
                {
                    string username, password;
                    cout << "masukkan username user: ";
                    cin >> username;
                    cout << "masukkan password user: ";
                    cin >> password;

                    User *user = new User(username, password);
                    dashboard.addUser(user);
                    cout << "user " << username <<" berhasil ditambahkan" << endl;
                    break;
                }

                case 2:
                {
                    string username, activity;
                    cout << "masukkan username user: ";
                    cin >> username;
                    cout << "masukkan kegiatan: ";
                    cin.ignore(); 
                    getline(cin, activity);

                    dashboard.addActivity(username, activity);
                    break;
                }

                case 3:
                    dashboard.displayUserActivities();
                    break;

                default:
                    cout << "ga bener lu" << endl;
                    break;
                }
            }

            break;
        }

        case 0:
            return 0; // keluar program

        default:
            cout << "ga bener lu" << endl;
            break;
        }
    }

    return 0;
}
