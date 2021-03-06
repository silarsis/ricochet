/* Ricochet - https://ricochet.im/
 * Copyright (C) 2014, John Brooks <john.brooks@dereferenced.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 *    * Neither the names of the copyright owners nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CRYPTOKEY_H
#define CRYPTOKEY_H

#include <QString>
#include <QSharedData>
#include <QExplicitlySharedDataPointer>

class CryptoKey
{
public:
    CryptoKey();
    CryptoKey(const CryptoKey &other) : d(other.d) { }
    ~CryptoKey();

    static void test(const QString &file);

    bool loadFromData(const QByteArray &data, bool privateKey = false);
    bool loadFromFile(const QString &path, bool privateKey = false);
    void clear();

    bool isValid() const { return d.data() != 0; }
    bool isLoaded() const { return d.data() && d->key != 0; }
    bool isPrivate() const;

    QByteArray publicKeyDigest() const;
    QByteArray encodedPublicKey() const;
    QString torServiceID() const;

    /* Raw signatures; no digest */
    QByteArray signData(const QByteArray &data) const;
    bool verifySignature(const QByteArray &data, QByteArray signature) const;

private:
    struct Data : public QSharedData
    {
        typedef struct rsa_st RSA;
        RSA *key;

        Data(RSA *k = 0) : key(k) { }
        ~Data();
    };

    QExplicitlySharedDataPointer<Data> d;
};

QByteArray torControlHashedPassword(const QByteArray &password);

#endif // CRYPTOKEY_H
