#include "stdafx.h"
#include "secret.h"

char * lpszPasswordDict[] = {
    " ",
    "anonymous",
    "sa",
    "SA",
    "123456",
    "1",
    "123",
    "123123",
    "112233",
    "1234",
    "12345",
    "1234567",
    "12345678",
    "123456789",
    "1234567890",
    "0123456789",
    "Email",
    "email",
    "a123456",
    "admin",
    "qaz123",
    "1sanjose",
    "123.com",
    "525464",
    "123.qwe",
    "process",
    "temp",
    "1234qwer",
    "123asd",
    "Chred1433",
    "admin888",
    "1qaz3edc",
    "1qaz4rfv",
    "3edc4rfv",
    "4rfv5tgb",
    "5tgb6yhn",
    "6yhn7ujm",
    "7ujm8ik,",
    "aaa123!@#",
    "test1234",
    "1qaz@wsx#edc",
    "admin123456789",
    "qazwsx123",
    "qaz123wsx",
    "admin123",
    "password",
    "qwe123",
    "qweqwe",
    "aaa123",
    "pass@word1",
    "Password1234",
    "asd@123",
    "Sa@123",
    "!QAZxsw2",
    "masterkey",
    "sa123!@#",
    "abc@123",
    "!QAZ1qaz",
    "123@abcd",
    "111",
    "111111",
    "11111111",
    "11111111111",
    "1111",
    "888",
    "888888",
    "8888",
    "88888888",
    "666",
    "6666",
    "666666",
    "66666666",
    "abc123",
    "123abc",
    "1ab2c3",
    "zxcvbn",
    "zxcvbnm",
    "asdasd",
    "asdfghjkl",
    "asd123",
    "qweasd",
    "qweasdzxc",
    "QAZWSX",
    "123qwe@#",
    "admin@123",
    "123abc!@#",
    "1qaz2ws",
    "zaq12wsx",
    "P@SSW0rd",
    "a123",
    "a111111",
    "a123456789",
    "a1234",
    "p@ssw0rd",
    "P@ssW0rd",
    "P@ssw0rd",
    "aa123456",
    "1234abcd",
    "qwer1234!@#$",
    "159357",
    "336699",
    "1qaz2wsx",
    "paSSword",
    "password1",
    "654321",
    "qwerty",
    "123456a",
    "pa$$word",
    "passw0rd",
    "PasswOrd",
    "qwe.123",
    "zxc123!@#",
    "root",
    "a1b2c3",
    "admin123456",
    "pass",
    "pass123",
    "zxc123",
    "user",
    "11223344",
    "asd123456",
    "password123",
    "121212",
    "monkey",
    "princess",
    "guest",
    "123123123",
    "qazwsx",
    "computer",
    "12345a",
    "1111222",
    "111222",
    "123456789a",
    "000000",
    "1qazXSW@",
    "1qaz@WSX",
    "123!@#qwe",
    "1q2w3e4r5t",
    "qwertyuiop",
    "q1w2e3",
    "123321",
    "123qwe",
    "1q2w3e4r",
    "7777777",
    "987654321",
    "qwerty1",
    "222222",
    "1g2w3e4r",
    "zag12wsx",
    "system",
    "555555",
    "1q2w3e",
    "admin123!@#",
    "P@$$w0rd",
    "123698745",
    "asdfjkl",
    "21212121",
    "456852",
    "a12345678",
    "money123",
    "1qazxsw2",
    "1234rewq",
    "12qwaszx",
    "22222222",
    "zxcvbnm123",
    "password11",
    "zxcv",
    "a1b2c3d4",
    "qqqqqq",
    "aaa111",
    "111aaa",
    "369369369",
    "369369",
    "123454321",
    "qw123321",
    "asdasdasd",
    "111222333",
    "asdfghj",
    "ypbwkfyjhyhgzj",
    "ly1234",
    "vice_1433 vice",
    "sa@123",
    "Admin123",
    "123qweASD",
    "Abc123",
    "Sa123456",
    "sa123456",
    "sa123",
    "target123",
    "root123",
    "mssql",
    "sqlserver",
    "server",
    "client",
    "login",
    "test",
    "qq123456",
    "a123123",
    "18n28n24a5",
    "test1",
    "QAZ123",
    "Aa123456.",
    "test123",
    "super",
    "text",
    "vice",
    "ifuckyounow",
    "zXJl@mwZ",
    "!qaz1QAZ",
    "!qaz2WSX",
    "!qaz3wsx",
    "!qaz@WSX",
    "qqaazz",
    "z123456",
    "zaqwsx",
    "1qwerty",
    "musica",
    "!QAZ2wsx",
    "abcd1234",
    "123456aa",
    "1234321",
    "123zxc",
    "123321a",
    "123qaz",
    "qwer123",
    "qwerty123",
    "zxcvbnm,./",
    "q1w2Q!W@",
    "1qazxcvbnm,./",
    "bw99588399",
    "huweishen.com",
    "huweishen",
    "zkeys",
    "piress",
    "letmein",
    "Master",
    "master",
    "model",
    "tempdb",
    "zjsxidc123",
    "0okmnji9",
    "msdb",
    "superman",
    "sql123456",
    "baseball",
    "welcome",
    "sa@qaz",
    "sa@qazwsx",
    "123qweasd",
    "welcometo",
    "mypassword",
    "caonima",
    "147258",
    "qwe!@#123",
    "123qwe!@#",
    "qaz#@!321",
    "qwe123123",
    "a123.321",
    "a321.123",
    "a123.123",
    "a321.321",
    "zaq1xsw2",
    "qwert12345",
    "PassWord",
    "zxcasd",
    "qaswed",
    "1qaz@2wsx",
    "qaz1wsx2",
    "qwaszx!@#",
    "qazwsx!@#",
    "qwe123456",
    "1314520",
    "147258369",
    "idc123456",
    "123.654",
    "123.456"
    "123.456.789",
    "123.456.789a",
    "123.456a",
    "PASSWORD",
    "1qw23er4",
    "aaaaaa",
    "zaq!@wsx",
    "aabbcc",
    "a12345",
    "zxcmnb",
    "zxcv1234",
    "2wsxdr5 ",
    "2wsx3edc ",
    "2w3e4r ",
    "234fd ",
    "enkj.1qazxdr5",
    "123!@#",
    "idc123!@#",
    "3dgidc@))*",
    "ywinidc56#@!",
    "aini",
    "gjp",
    "aini1314520",
    "caonimagebi",
    "football",
    "football123",
    "administrator",
    "adminsa",
    "admin@sa",
    "admin@1234",
    "admin@888",
    "qq123.com",
    "159753",
    "111qqq..."
};

BOOL secret::GetPasswordDict(vector<CString>& dict)
{
    CString szPass;
    for (int i = 0; i < sizeof(lpszPasswordDict) / sizeof(char*); ++i)
    {
        szPass = CA2W(lpszPasswordDict[i]);
        dict.push_back(szPass);
    }

    return TRUE;
}
