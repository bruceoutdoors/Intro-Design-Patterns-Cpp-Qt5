#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H


#include <QProcess>

/** auth-style password manager, for use with htpasswd */
class PasswordManager : public QProcess {
	Q_OBJECT
	public:
	
	PasswordManager();
	virtual ~PasswordManager() {}

	/** @return the SHA1 password from the "auth" file, if it is there.
		or a blank string, if the user is not registered yet */
	QString getPassword(QString userName);

	/** @return true if the user's password is valid. */
	bool checkPassword (QString userName, QString password);

	/** Creates a user
		@return true if successful, false if not (such as if the user already exists)
	*/
	bool addUser(QString userName, QString password);
	
	/**
	  Changes password if the oldPassword is valid 
	  */
	bool changePassword(QString userName, QString oldPassword, QString newPassword);
	
    protected:
	void setPassword(QString userName, QString password);
	
};

#endif        //  #ifndef PASSWORDMANAGER_H

