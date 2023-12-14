#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class PembuatToken
{
public:
    double hasilkanToken()
    {
        return rand();
    }
};

class Tampilan
{
public:
    Tampilan() {}

    virtual ~Tampilan() {}

    virtual void notifikasi() = 0;
    void tampilkanToken(double token)
    {
        cout << "token dihasilkan: " << token << endl;
    }
};

class Pengguna : public Tampilan
{
private:
    PembuatToken pembuatToken;
    vector<Pengguna *> teman;

public:
    Pengguna() {}

    ~Pengguna() {}

    void pembuatanToken()
    {
        token = pembuatToken.hasilkanToken();
    }

    void daftarPengguna(const string &namaPengguna, const string &kataSandi)
    {
        this->namaPengguna = namaPengguna;
        this->kataSandi = kataSandi;
        pembuatanToken();
        cout << "Nama Pengguna: " << this->namaPengguna << endl;
        cout << "Kata Sandi: " << this->kataSandi << endl;
        tampilkanToken(token);
    }

    void tambahTeman(Pengguna *temanPengguna)
    {
        teman.push_back(temanPengguna);
    }

    void tampilkanTeman() const
    {
        cout << "Teman dari " << getNamaPengguna() << ": " ;
        for (int i = 0; i < teman.size(); ++i)
        {
            cout << teman[i]->getNamaPengguna() << endl;
        }
    }

    void notifikasi() override
    {
        cout << "pengguna dibuat oleh Pengguna" << endl;
        tampilkanToken(token);
    }

    string getNamaPengguna() const
    {
        return namaPengguna;
    }

    string getKataSandi() const
    {
        return kataSandi;
    }

    double getToken() const
    {
        return token;
    }

    const vector<Pengguna *> &getTeman() const
    {
        return teman;
    }

protected:
    string namaPengguna;
    string kataSandi;
    double token;
};

class Admin : public Pengguna
{
private:
    bool terotentikasi;

public:
    Admin() : terotentikasi(false) {}

    ~Admin() {}

    void autentikasi()
    {
        terotentikasi = true;
    }

    bool sudahAutentikasi() const
    {
        return terotentikasi;
    }

    void notifikasi() override
    {
        cout << "pengguna dibuat oleh Admin" << endl;
        tampilkanToken(getToken());
    }
};

class ManajerHubungan
{
private:
    vector<Pengguna *> pengguna;

public:
    void tambahPengguna(Pengguna *penggunaBaru)
    {
        pengguna.push_back(penggunaBaru);
    }

    void tampilkanHubungan() const
    {
        cout << "Hubungan:" << endl;

        for (int i = 0; i < pengguna.size(); ++i)
        {
            const vector<Pengguna *> &teman = pengguna[i]->getTeman();
            for (int j = 0; j < teman.size(); ++j)
            {
                cout << pengguna[i]->getNamaPengguna() << " berteman dengan " << teman[j]->getNamaPengguna() << endl;
            }
        }
    }
};

class Dasbor
{
private:
    vector<Admin *> admin;
    vector<Pengguna *> pengguna;
    ManajerHubungan manajerHubungan;

public:
    Dasbor() {}

    ~Dasbor()
    {
        for (int i = 0; i < admin.size(); ++i)
        {
            delete admin[i];
        }
        for (int i = 0; i < pengguna.size(); ++i)
        {
            delete pengguna[i];
        }
    }

    const vector<Admin *> &getAdmin() const
    {
        return admin;
    }

    const vector<Pengguna *> &getPengguna() const
    {
        return pengguna;
    }

    void tampilkanSemuaPengguna() const
    {
        cout << "Semua Pengguna:" << endl;

        for (int i = 0; i < admin.size(); ++i)
        {
            cout << "Admin Nama Pengguna: " << admin[i]->getNamaPengguna() << " Token: " << admin[i]->getToken() << endl;
        }

        for (int i = 0; i < pengguna.size(); ++i)
        {
            cout << "Pengguna Nama Pengguna: " << pengguna[i]->getNamaPengguna() << " Token: " << pengguna[i]->getToken() << endl;
        }
    }

    void tambahAdmin(Admin *adminBaru)
    {
        admin.push_back(adminBaru);
    }

    void tambahPengguna(Pengguna *penggunaBaru)
    {
        pengguna.push_back(penggunaBaru);
        manajerHubungan.tambahPengguna(pengguna.back());
    }

    Admin *dapatkanAdminTerotentikasi() const
    {
        for (int i = 0; i < admin.size(); ++i)
        {
            if (admin[i]->sudahAutentikasi())
            {
                return admin[i];
            }
        }
        return nullptr;
    }

    void tambahPersahabatan(Pengguna &pengguna1, Pengguna &pengguna2)
    {
        pengguna1.tambahTeman(&pengguna2);
        pengguna2.tambahTeman(&pengguna1);
    }

    ManajerHubungan &dapatkanManajerHubungan()
    {
        return manajerHubungan;
    }
};

int main()
{
    srand(time(0));

    Dasbor dasbor;

    while (true)
    {
        cout << "Pilihan:" << endl;
        cout << "1. Registrasi sebagai Admin" << endl;
        cout << "2. Registrasi sebagai Pengguna" << endl;
        cout << "3. Masuk Dasbor (Hanya Admin)" << endl;
        cout << "4. Keluar" << endl;

        int pilihan;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        {
            cout << "Masukkan Nama Pengguna Admin:" << endl;
            string namaPenggunaAdmin;
            cin >> namaPenggunaAdmin;

            cout << "Masukkan Kata Sandi Admin:" << endl;
            string kataSandiAdmin;
            cin >> kataSandiAdmin;

            Admin *adminBaru = new Admin();
            adminBaru->daftarPengguna(namaPenggunaAdmin, kataSandiAdmin);
            adminBaru->autentikasi();
            dasbor.tambahAdmin(adminBaru);

            cout << "Admin berhasil terdaftar!" << endl;
            break;
        }
        case 2:
        {
            cout << "Masukkan Nama Pengguna:" << endl;
            string namaPengguna;
            cin >> namaPengguna;

            cout << "Masukkan Kata Sandi:" << endl;
            string kataSandi;
            cin >> kataSandi;

            Pengguna *penggunaBaru = new Pengguna();
            penggunaBaru->daftarPengguna(namaPengguna, kataSandi);
            dasbor.tambahPengguna(penggunaBaru);
            break;
        }
        case 3:
        {
            cout << "Masukkan Nama Pengguna Admin:" << endl;
            string namaPenggunaAdmin;
            cin >> namaPenggunaAdmin;

            cout << "Masukkan Kata Sandi Admin:" << endl;
            string kataSandiAdmin;
            cin >> kataSandiAdmin;

            bool adminTerotentikasi = false;
            Admin *adminTerotentikasiObj = nullptr;
            const vector<Admin *> &adminList = dasbor.getAdmin();
            for (int i = 0; i < adminList.size(); ++i)
            {
                Admin *adminBaru = adminList[i];
                if (adminBaru->getNamaPengguna() == namaPenggunaAdmin && kataSandiAdmin == adminBaru->getKataSandi())
                {
                    adminTerotentikasi = true;
                    adminTerotentikasiObj = adminBaru;
                    cout << "Admin berhasil masuk!" << endl;
                    break;
                }
            }

            if (!adminTerotentikasi)
            {
                cout << "Masuk gagal. Periksa kembali nama pengguna dan kata sandi admin." << endl;
            }
            else
            {
                while (true)
                {
                    cout << "Dasbor Admin:" << endl;
                    cout << "1. Tampilkan semua pengguna" << endl;
                    cout << "2. Tambahkan Teman" << endl;
                    cout << "3. Tampilkan Teman" << endl;
                    cout << "4. Keluar" << endl;

                    int pilihanDasbor;
                    cout << "Pilih: ";
                    cin >> pilihanDasbor;

                    switch (pilihanDasbor)
                    {
                    case 1:
                    {
                        const vector<Admin *> &adminList = dasbor.getAdmin();
                        for (int i = 0; i < adminList.size(); ++i)
                        {
                            cout << "Admin Nama Pengguna: " << adminList[i]->getNamaPengguna() << " Token: " << adminList[i]->getToken() << endl;
                        }

                        const vector<Pengguna *> &penggunaList = dasbor.getPengguna();
                        for (int i = 0; i < penggunaList.size(); ++i)
                        {
                            cout << "Pengguna Nama Pengguna: " << penggunaList[i]->getNamaPengguna() << " Token: " << penggunaList[i]->getToken() << endl;
                        }
                        break;
                    }
                    case 2:
                    {
                        string namaPenggunaTeman;
                        cout << "Masukkan Nama Pengguna Teman:" << endl;
                        cin >> namaPenggunaTeman;

                        Pengguna *temanPengguna = nullptr;
                        const vector<Pengguna *> &penggunaList = dasbor.getPengguna();
                        for (int i = 0; i < penggunaList.size(); ++i)
                        {
                            if (penggunaList[i]->getNamaPengguna() == namaPenggunaTeman)
                            {
                                temanPengguna = penggunaList[i];
                                break;
                            }
                        }

                        if (temanPengguna != nullptr)
                        {
                            dasbor.tambahPersahabatan(*adminTerotentikasiObj, *temanPengguna);
                            cout << "Teman berhasil ditambahkan!" << endl;
                        }
                        else
                        {
                            cout << "Pengguna dengan nama pengguna tersebut tidak ditemukan." << endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        const vector<Pengguna *> &penggunaList = dasbor.getPengguna();
                        for (int i = 0; i < penggunaList.size(); ++i)
                        {
                            cout << "Teman dari " << penggunaList[i]->getNamaPengguna() << ": ";
                            const vector<Pengguna *> &teman = penggunaList[i]->getTeman();
                            for (int j = 0; j < teman.size(); ++j)
                            {
                                cout << teman[j]->getNamaPengguna() << endl;
                            }
                        }
                        break;
                    }
                    case 4:
                        cout << "Keluar Admin." << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid." << endl;
                    }

                    if (pilihanDasbor == 4)
                    {
                        break;
                    }
                }
            }
            break;
        }
        case 4:
            cout << "Program selesai." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
