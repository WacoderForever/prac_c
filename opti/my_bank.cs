using System;
using System.IO;
using System.Text;

public struct Person
{
    public string fname;
    public string phone;
    public string account_no;
    public string pass;
    public float balance;
}

class BankSystem
{
    static void Main()
    {
        string filename;
        string login;
        string pass2;
        Person currentUser;
        int choice = 0;

        while (choice != 6)
        {
            DisplayMenu();
            Console.Write("\t\tEnter choice: ");
            if (!int.TryParse(Console.ReadLine(), out choice))
            {
                Console.WriteLine("\t\tInvalid input. Please enter a number.");
                continue;
            }

            switch (choice)
            {
                case 1:
                    CreateAccount(out currentUser);
                    break;

                case 2:
                    if (LogIn(out currentUser, out login, out pass2, out filename))
                    {
                        Console.Clear();
                        Console.WriteLine($"\t\tWelcome back {currentUser.fname}!!");
                        HandleUserOptions(ref currentUser, filename);
                    }
                    else
                    {
                        Console.WriteLine("\t\tWrong password or account does not exist.");
                    }
                    break;

                case 6:
                    Console.WriteLine("\t\tExiting the bank system.Thank you for banking with us Goodbye!");
                    break;

                default:
                    Console.WriteLine("\t\tInvalid option!!!");
                    break;
            }
        }
    }

    static void DisplayMenu()
    {
        Console.WriteLine("\t\t###################################");
        Console.WriteLine("\t\t## WELCOME TO COdex BANK SYSTEM ##");
        Console.WriteLine("\t\t##################################");
        Console.WriteLine("\t\tEnter 1 to create account.");
        Console.WriteLine("\t\tEnter 2 to log in.");
        Console.WriteLine("\t\tEnter 6 to exit.");
    }

    static string GetPassword()
    {
        Console.Write("\t\tEnter password: ");
        StringBuilder password = new StringBuilder();

        while (true)
        {
            ConsoleKeyInfo key = Console.ReadKey(true);

            if (key.Key == ConsoleKey.Enter)
            {
                break;
            }
            else if (key.Key == ConsoleKey.Backspace)
            {
                if (password.Length > 0)
                {
                    password.Remove(password.Length - 1, 1);
                    Console.Write("\b \b");
                }
            }
            else
            {
                password.Append(key.KeyChar);
                Console.Write("*");
            }
        }

        Console.WriteLine();
        return password.ToString();
    }

    static void CreateAccount(out Person user)
    {
        Console.Clear();
        Console.Write("\t\tEnter first name: ");
        user.fname = Console.ReadLine();
        Console.Write("\t\tEnter phone number: ");
        user.phone = Console.ReadLine();
        Console.Write("\t\tEnter account number: ");
        user.account_no = Console.ReadLine();
        user.pass = GetPassword();
        Console.Write("\t\tEnter account balance: ");

        if (!float.TryParse(Console.ReadLine(), out user.balance) || user.balance < 0)
        {
            Console.WriteLine("\t\tInvalid input for balance. Please enter a valid amount.");
            return;
        }

        string filename = user.phone + ".dat";

        if (File.Exists(filename))
        {
            Console.WriteLine("\t\tSorry, the account already exists.");
        }
        else
        {
            using (StreamWriter writer = new StreamWriter(filename))
            {
                writer.WriteLine(user.fname);
                writer.WriteLine(user.phone);
                writer.WriteLine(user.account_no);
                writer.WriteLine(user.pass);
                writer.WriteLine(user.balance);
            }

            Console.WriteLine("\t\tAccount registration successful.");
        }
    }

    static bool LogIn(out Person user, out string login, out string pass2, out string filename)
    {
        Console.Clear();
        Console.Write("\t\tEnter phone number: ");
        login = Console.ReadLine();
        pass2 = GetPassword();
        filename = login + ".dat";

        user = new Person();

        if (File.Exists(filename))
        {
            using (StreamReader reader = new StreamReader(filename))
            {
                user.fname = reader.ReadLine();
                user.phone = reader.ReadLine();
                user.account_no = reader.ReadLine();
                user.pass = reader.ReadLine();
                user.balance = float.Parse(reader.ReadLine());
            }

            return user.pass == pass2;
        }
        else
        {
            Console.WriteLine("\t\tAccount does not exist.");
            return false;
        }
    }

    static void HandleUserOptions(ref Person user, string filename)
    {
        int option = 0;

        while (option != 6)
        {
            DisplayUserMenu();
            Console.Write("\t\tEnter option: ");

            if (!int.TryParse(Console.ReadLine(), out option))
            {
                Console.WriteLine("\t\tInvalid input. Please enter a number.");
                continue;
            }

            switch (option)
            {
                case 1:
                    Deposit(ref user, filename);
                    break;

                case 2:
                    Withdraw(ref user, filename);
                    break;

                case 3:
                    TransferFunds(ref user, filename);
                    break;

                case 4:
                    Console.WriteLine($"\t\tYour current account balance is {user.balance:C2}");
                    break;

                case 5:
                    ChangePassword(ref user, filename);
                    break;

                case 6:
                    Console.WriteLine("\t\tLogging out.....");
                    break;

                default:
                    Console.WriteLine("\t\tInvalid option!!!");
                    break;
            }
        }
    }

    static void DisplayUserMenu()
    {
        Console.WriteLine("\t\tEnter 1 to deposit.");
        Console.WriteLine("\t\tEnter 2 to withdraw.");
        Console.WriteLine("\t\tEnter 3 to send money.");
        Console.WriteLine("\t\tEnter 4 to check balance.");
        Console.WriteLine("\t\tEnter 5 to change password.");
        Console.WriteLine("\t\tEnter 6 to log out.");
    }

    static void Deposit(ref Person user, string filename)
    {
        Console.Clear();
        Console.Write("\t\tEnter amount to deposit: ");
        float depositAmount;

        if (!float.TryParse(Console.ReadLine(), out depositAmount) || depositAmount <= 0)
        {
            Console.WriteLine("\t\tInvalid input for deposit. Please enter a valid amount.");
            return;
        }

        using (StreamWriter writer = new StreamWriter(filename))
        {
            user.balance += depositAmount;
            writer.WriteLine(user.fname);
            writer.WriteLine(user.phone);
            writer.WriteLine(user.account_no);
            writer.WriteLine(user.pass);
            writer.WriteLine(user.balance);
        }

        Console.WriteLine($"\t\tDeposit of Ksh.{depositAmount:C2} was successful. Your account balance is {user.balance:C2}.");
    }

    static void Withdraw(ref Person user, string filename)
    {
        Console.Clear();
        Console.Write("\t\tEnter amount to withdraw: ");
        float withdrawAmount;

        if (!float.TryParse(Console.ReadLine(), out withdrawAmount) || withdrawAmount <= 0)
        {
            Console.WriteLine("\t\tInvalid input for withdrawal. Please enter a valid amount.");
            return;
        }

        if (withdrawAmount > user.balance)
        {
            Console.WriteLine($"\t\tCannot withdraw that amount. Your current balance is {user.balance:C2}");
        }
        else
        {
            using (StreamWriter writer = new StreamWriter(filename))
            {
                user.balance -= withdrawAmount;
                writer.WriteLine(user.fname);
                writer.WriteLine(user.phone);
                writer.WriteLine(user.account_no);
                writer.WriteLine(user.pass);
                writer.WriteLine(user.balance);
            }

            Console.WriteLine($"\t\tWithdrawal of Ksh.{withdrawAmount:C2} was successful. Your account balance is {user.balance:C2}.");
        }
    }

    static void TransferFunds(ref Person user, string senderFilename)
    {
        Console.Clear();
        Console.Write("\t\tEnter account to send money: ");
        string recipientAccount = Console.ReadLine();

        if (!File.Exists(recipientAccount + ".dat"))
        {
            Console.WriteLine("\t\tRecipient account does not exist.");
            return;
        }

        float depositAmount;
        Console.Write("\t\tEnter amount to send: ");
        while (!float.TryParse(Console.ReadLine(), out depositAmount) || depositAmount <= 0)
        {
            Console.WriteLine("\t\tInvalid input. Please enter a valid amount.");
            Console.Write("\t\tEnter amount to send: ");
        }

        Person recipient = new Person();
        using (StreamReader recipientReader = new StreamReader(recipientAccount + ".dat"))
        {
            recipient.fname = recipientReader.ReadLine();
            recipient.phone = recipientReader.ReadLine();
            recipient.account_no = recipientReader.ReadLine();
            recipient.pass = recipientReader.ReadLine();
            recipient.balance = float.Parse(recipientReader.ReadLine());
        }

        if (depositAmount <= user.balance)
        {
            using (StreamWriter senderWriter = new StreamWriter(senderFilename))
            {
                user.balance -= depositAmount;
                senderWriter.WriteLine(user.fname);
                senderWriter.WriteLine(user.phone);
                senderWriter.WriteLine(user.account_no);
                senderWriter.WriteLine(user.pass);
                senderWriter.WriteLine(user.balance);
            }

            using (StreamWriter recipientWriter = new StreamWriter(recipientAccount + ".dat"))
            {
                recipient.balance += depositAmount;
                recipientWriter.WriteLine(recipient.fname);
                recipientWriter.WriteLine(recipient.phone);
                recipientWriter.WriteLine(recipient.account_no);
                recipientWriter.WriteLine(recipient.pass);
                recipientWriter.WriteLine(recipient.balance);
            }

            Console.WriteLine($"\t\tTransfer to {recipient.fname} was successful.");
            Console.WriteLine($"\t\tYour current balance is {user.balance:C2}");
        }
        else
        {
            Console.WriteLine($"\t\tInsufficient balance to send {depositAmount:C2}! Your current balance is {user.balance:C2}");
        }
    }

    static void ChangePassword(ref Person user, string filename)
    {
        Console.Clear();
        string currentPassword;
        Console.WriteLine("\t\tEnter current password");
        currentPassword = GetPassword();

        if (currentPassword == user.pass)
        {
            Console.WriteLine("\t\tEnter new password");
            string newPassword = GetPassword();

            using (StreamWriter writer = new StreamWriter(filename))
            {
                user.pass = newPassword;
                writer.WriteLine(user.fname);
                writer.WriteLine(user.phone);
                writer.WriteLine(user.account_no);
                writer.WriteLine(user.pass);
                writer.WriteLine(user.balance);
            }

            Console.WriteLine($"\t\tPassword change successful. Your new password is {user.pass}");
        }
        else
        {
            Console.WriteLine("\t\tWrong password");
        }
    }
}

