#include "StealthScanCriterion.hpp"

namespace Xeth{

using Ethereum::PublicKeySerializer;
using Ethereum::Data;
using Ethereum::Literal;
using Ethereum::HexEncoder;

StealthScanCriterion::StealthScanCriterion(const StealthKey &key) :
    ScanCriterion(Literal(Ethereum::Stealth::Address(key))),
    _key(key)
{}

StealthScanCriterion::StealthScanCriterion(const StealthKey &key, const Ethereum::Stealth::Address &address) :
    ScanCriterion(Literal(address)),
    _key(key)
{}


void StealthScanCriterion::uncoverStealthPayment
(
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const char *data,
    size_t dataSize,
    time_t timestamp,
    ScanResult &result
)
{
    PublicKeySerializer serializer;
    try
    {
        Ethereum::PublicKey ephem = serializer.unserialize(data, dataSize);
        StealthResolver resolver(_key);
        Ethereum::Stealth::SharedSecret secret;
        if(resolver.uncover(Ethereum::Address(to), ephem, secret))
        {
            QJsonObject tx;
            tx.insert("category", QString(TransactionCategory::ToString(TransactionCategory::Received)));
            tx.insert("hash", QString(hash.c_str()));
            tx.insert("from",  QString(from.c_str()));
            tx.insert("to", QString(to.c_str()));
            tx.insert("amount", QString(boost::lexical_cast<std::string>(amount).c_str()));
            tx.insert("timestamp", (int)timestamp);
            tx.insert("stealth", QString(getAddress()));
            result.transactions.push_back(tx);

            HexEncoder encoder;
            QJsonObject sp;
            sp.insert("address", QString(to.c_str()));
            sp.insert("secret", QString(encoder.encode(secret.begin(), secret.end()).c_str()));
            sp.insert("txid", QString(hash.c_str()));
            sp.insert("stealth", QString(getAddress()));
            tx.insert("timestamp", (int)timestamp);
            result.stealthPayments.push_back(sp);
        }
    }
    catch(...)
    {}
}

void StealthScanCriterion::processTransaction
(
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const std::string &data,
    time_t timestamp,
    ScanResult &result
)
{
    size_t dataSize = data.size();

    if(dataSize == 66 || dataSize == 130 || ((dataSize == 68 || dataSize == 132)&&data[0]=='0'&&(data[1]=='x'||data[1]=='X')))
    {
        uncoverStealthPayment(hash, from, to, amount, data.data(), dataSize, timestamp, result);
    }
}


}
