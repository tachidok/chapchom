#ifndef CC_READ_DATA_THREAD_H
#define CC_READ_DATA_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

// Sockets communication
#include <SFML/Network.hpp>

#define SOCKET_LISTEN_PORT_NUMBER 45678

enum Connection_status {CONNECTED, DISCONNECTED};

// This class is in charge of reading data from ethernet or a serial
// connection. The reading is performed using a thread thus the "drawing"
// is not interrupted by the reading of the data
class cc_read_data_thread : public QObject
{
    Q_OBJECT
public:
    explicit cc_read_data_thread(QObject *parent = 0);

    // Setup the thread
    void setup(QThread &thread);

    // Returns the current connection status
    inline Connection_status status(){return Status;}

signals:

    void finished();

public slots:

    // Implements the "run" method of a thread
    void run_thread();

private:

    // In charge of initialising the communication/connection with the external
    // data source
    void initialise_communication();

    // Listen for connections
    sf::TcpListener Listener;

    // In charge of dealing with a receiving connection (a client)
    sf::TcpSocket Client;

    Connection_status Status;

};

#endif // CC_READ_DATA_THREAD_H
