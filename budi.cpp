#include <iostream>
#include <string>

using namespace std;

const int MAX_ADMINS = 3;
const int MAX_USERS = 100;

class Display
{
public:
    virtual ~Display() = default;
    virtual void notification() const = 0;
};

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

class Admin : public User
{
public:
    Admin(const string &username, const string &password) : User(username, password) {}

    void notification() const override
    {
        cout << "Admin: " << username << endl;
    }
};

class Dashboard
{
private:
    User **users;
    int userCount;
    string *userActivities[MAX_USERS];
    int **adjacencyList; 

public:
    Dashboard() : users(new User *[MAX_ADMINS]), userCount(0)
    {
        for (int i = 0; i < MAX_USERS; ++i)
        {
            userActivities[i] = nullptr;
        }

        adjacencyList = new int *[MAX_ADMINS + MAX_USERS];
        for (int i = 0; i < MAX_ADMINS + MAX_USERS; ++i)
        {
            adjacencyList[i] = new int[MAX_ADMINS + MAX_USERS];
            for (int j = 0; j < MAX_ADMINS + MAX_USERS; ++j)
            {
                adjacencyList[i][j] = 0; 
            }
        }
    }

    ~Dashboard()
    {
        for (int i = 0; i < userCount; ++i)
        {
            delete users[i];
        }
        delete[] users;

        for (int i = 0; i < MAX_USERS; ++i)
        {
            delete userActivities[i];
        }

        for (int i = 0; i < MAX_ADMINS + MAX_USERS; ++i)
        {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
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
            delete user;
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

    void addConnection(int userIndex1, int userIndex2)
    {
        adjacencyList[userIndex1][userIndex2] = 1;
        adjacencyList[userIndex2][userIndex1] = 1;
    }

    void displayConnections(int userIndex) const
    {
        cout << "=== Connections for User " << userIndex << " ===" << endl;
        for (int i = 0; i < MAX_ADMINS + MAX_USERS; ++i)
        {
            if (adjacencyList[userIndex][i] == 1)
            {
                cout << "Connected User: " << i << endl;
            }
        }
        cout << "=============================" << endl;
    }

    int *getConnections(int userIndex) const
    {
        return adjacencyList[userIndex];
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

            if (dashboard.isAdminLimitReached())
            {
                cout << "dah penuh" << endl;
            }
            else
            {
                Admin *admin = new Admin(username, password);
                dashboard.addUser(admin);
                cout << "admin " << username << " berhasil ditambahkan" << endl;
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
            cout << "User " << username << " berhasil ditambahkan" << endl;
            break;
        }

        case 3:
        {
            dashboard.displayUsers();

            while (true)
            {
                cout << "Pilihan Dashboard:" << endl;
                cout << "1. tambah user" << endl;
                cout << "2. tambah kegiatan user" << endl;
                cout << "3. tampilkan kegiatan user" << endl;
                cout << "4. tampilkan koneksi user" << endl; 
                cout << "5. cek koneksi antar user" << endl; 
                cout << "0. keluar dari dashboard" << endl;

                int dashboardChoice;
                cout << "pilihan: ";
                cin >> dashboardChoice;

                if (dashboardChoice == 0)
                {
                    break;
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
                    cout << "user " << username << " berhasil ditambahkan" << endl;
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

                case 4:
                {
                    int userIndex;
                    cout << "Masukkan indeks user: ";
                    cin >> userIndex;
                    dashboard.displayConnections(userIndex);
                    break;
                }

                case 5:
                {
                    int userIndex1, userIndex2;
                    cout << "Masukkan indeks user pertama: ";
                    cin >> userIndex1;
                    cout << "Masukkan indeks user kedua: ";
                    cin >> userIndex2;

                    bool connected = false;
                    for (int i = 0; i < MAX_ADMINS + MAX_USERS; ++i)
                    {
                        if (dashboard.getConnections(userIndex1)[i] == 1 && dashboard.getConnections(userIndex2)[i] == 1)
                        {
                            connected = true;
                            break;
                        }
                    }

                    if (connected)
                        cout << "User " << userIndex1 << " dan User " << userIndex2 << " terhubung." << endl;
                    else
                        cout << "User " << userIndex1 << " dan User " << userIndex2 << " tidak terhubung." << endl;

                    break;
                }

                default:
                    cout << "ga bener lu" << endl;
                    break;
                }
            }

            break;
        }

        case 0:
            return 0;

        default:
            cout << "ga bener lu" << endl;
            break;
        }
    }

    return 0;
}
