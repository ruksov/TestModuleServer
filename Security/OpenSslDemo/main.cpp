#include <QCoreApplication>
#include "chiper.h"

QByteArray getPublicKey()
{
    QByteArray testPublicKey;

    testPublicKey.append("-----BEGIN PUBLIC KEY-----\n");
    testPublicKey.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAp3g5QnyKXon9YI99VNY9\n");
    testPublicKey.append("2e/Xq3oIXtMak3/cCo7uPZX2mj+dEPGMg1s7pb4dzEQ//q1bwyHme6zMCuqADf2O\n");
    testPublicKey.append("ig3MrlhG0BN0+Mo+YJIIR1j/xgz9WDq9oWi8zzgSG6MG0u2JTPy4fkWHWfv+b2VH\n");
    testPublicKey.append("mhlkLTkulh8nJNNCvaBPkcJzyj6w77IChHybjxeIy2ThIZh2Mqo3Mrhmy2GxX7oz\n");
    testPublicKey.append("YC9OmARYrj5gGccaE/p3PCtLwKb4j3TIjhLOEt1zKr5e77iC5w1pOJ8hBLemj2qo\n");
    testPublicKey.append("Hq0YEWH6x65iYt5AfsWLXP3SWMk2Ev/PmNzQ2kkL2Vi90II4ay+0mVJJ4M18GNkw\n");
    testPublicKey.append("bQIDAQAB\n");
    testPublicKey.append("-----END PUBLIC KEY-----\n");

    return testPublicKey;
}

QByteArray getPrivateKey()
{
    QByteArray testPrivateKey;

    testPrivateKey.append("-----BEGIN RSA PRIVATE KEY-----\n");
    testPrivateKey.append("MIIEowIBAAKCAQEAp3g5QnyKXon9YI99VNY92e/Xq3oIXtMak3/cCo7uPZX2mj+d\n");
    testPrivateKey.append("EPGMg1s7pb4dzEQ//q1bwyHme6zMCuqADf2Oig3MrlhG0BN0+Mo+YJIIR1j/xgz9\n");
    testPrivateKey.append("WDq9oWi8zzgSG6MG0u2JTPy4fkWHWfv+b2VHmhlkLTkulh8nJNNCvaBPkcJzyj6w\n");
    testPrivateKey.append("77IChHybjxeIy2ThIZh2Mqo3Mrhmy2GxX7ozYC9OmARYrj5gGccaE/p3PCtLwKb4\n");
    testPrivateKey.append("j3TIjhLOEt1zKr5e77iC5w1pOJ8hBLemj2qoHq0YEWH6x65iYt5AfsWLXP3SWMk2\n");
    testPrivateKey.append("Ev/PmNzQ2kkL2Vi90II4ay+0mVJJ4M18GNkwbQIDAQABAoIBAH9T5RUr43hlqgPU\n");
    testPrivateKey.append("lRH/oh8lP/DcY6jVEIu81uwgJ/sjHc/BNgY/4PmuT/eASN+ZtJ5J6E7AY6D8jFZw\n");
    testPrivateKey.append("XNRGSC2muEyGSbDCWlkeS7bY0PqOLEnEboq6fptOKt/SXdItbW7Js26ZZxx6eKJt\n");
    testPrivateKey.append("+dFwS7RaQdQweb8iCHzzMvdB/71tw8tISlCooz7tujoMwmO+WLljkogzHnxiwNBE\n");
    testPrivateKey.append("elGyThauGFyH28RPUiF0uCoaheKG2dUg+Ijm+OnpHVbpurNWzyDZAUtMCvgU4RzE\n");
    testPrivateKey.append("f4oQ1jxrYtn8RIXT+0xYB7K3+UI6uskWrwzC259KB6oBsgKR5VCAiVMDBFQPPmym\n");
    testPrivateKey.append("kqws3IECgYEA10sQlhyyXwtoJ3caHPqHsLr9ZFANZ552QV1LjqhfknsiDyXUIroP\n");
    testPrivateKey.append("kxBE14+V/fUr+ZK71mwXDc/zJLLMlgAyvTS698zihbm9nt1FBtGe7Wilmpm8LhRf\n");
    testPrivateKey.append("uA8waz2wP5DlCVn2tw5zfXzBta0e6KbuFcRPIk7LE5EyzML5EgW5WAkCgYEAxyJU\n");
    testPrivateKey.append("5XL9ulPbiu06qPOciL/loNEDPgVndcnMLlDyWvno5gl7PWRvdh/P7uHC0nD/yrWU\n");
    testPrivateKey.append("a+KNQP7uHiTnu9PVlL6A/sKNlP3IPteUWJot9cmwHL+ur2eoV8Cka6vTPwtknKsh\n");
    testPrivateKey.append("3LtWNXN6nFEZzLKcwnapxx3J7UJN4SMlsiHCRkUCgYAglnwsPKvDNzbMwnpxaHqh\n");
    testPrivateKey.append("haxVQsjEpne/7R9CuLm+smS1ZkR1/TPeTtgcyN8rUbEWVd+Y1UOoE5H6PBY7nkwP\n");
    testPrivateKey.append("16t1Vs3y7+qD4XpRTemAhhaLEDorv2m9so7hrLTA6m3AvJ1bmBRjKj8oAMxs6tee\n");
    testPrivateKey.append("89gGmWajz5ag5+JLmBI2AQKBgGoORtjNHYUXFF4xaoSA+mV6jnnP18I4bpm1GCGy\n");
    testPrivateKey.append("yuDZKMkbU5+m1hY7ayr24iPiOtljS+EJj+GF5Jv5W9IVSDMoItuMEou/fd66Qi/O\n");
    testPrivateKey.append("LZwyBrHJBOg2dNoHp4oQwTlagANQwYAl5gwhrLOEHhF/Ly4CtPlvTBQotAGsDm+I\n");
    testPrivateKey.append("u0dhAoGBAL6o/FadExxMs2vBogjNOJLqGSVMYGDxguCmJ3+7+nFRV0H5vJXUG1Sy\n");
    testPrivateKey.append("hOSktCWFGPauFykgP2ouqT/IIGn8g+X8Fmb8esRqy3ryq8aYzUNtHE4peJ9Xb9Wk\n");
    testPrivateKey.append("OnFhD/pi7S5k4gAaN3e4qzpD3L3aqDy19mt5xC/Iq5ZbD9TyLKyH\n");
    testPrivateKey.append("-----END RSA PRIVATE KEY-----\n");

    return testPrivateKey;

}

void TestRSA()
{
    qDebug()<<"Loading keys";
    QByteArray testPrivateKey = getPrivateKey();
    QByteArray testPublicKey = getPublicKey();

    Chiper wraper;
    RSA* publickey = wraper.GetPublicKey(testPublicKey);
    RSA* privatekey = wraper.GetPrivateKey(testPrivateKey);

    QByteArray plain = "The man in black fled into the desert and the ... ";
    QByteArray encrypted = wraper.EncryptRSA(publickey, plain);
    QByteArray decrypted = wraper.DecryptRSA(privatekey, encrypted);
    qDebug()<<plain;
    qDebug()<<encrypted;
    qDebug()<<decrypted;
}

void GenRSAKeys()
{
    system("openssl genrsa -des3 -out private.pem 2048");
    system("openssl rsa -in private.pem -outform PEM -pubout -out public.pem");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Chiper test;
    QByteArray plain = "The man in black fled into the desert and the ... ";
    QByteArray encrypted = test.EncryptRSA(test.m_ptrPubKey, plain);
    QByteArray decrypted = test.DecryptRSA(test.m_ptrPrivKey, encrypted);
    qDebug()<<plain;
    qDebug()<<encrypted;
    qDebug()<<decrypted;
    return a.exec();
}
