#include "cc_read_data_thread.h"

cc_read_data_thread::cc_read_data_thread(QObject *parent) : QObject(parent)
{
    // Set the current status as disconnected
    Status = DISCONNECTED;
}

// ========================================================================
// In charge of initialising the communication/connection with the external
// data source and setting the thread
// ========================================================================
void cc_read_data_thread::setup(QThread &thread)
{
    // Connect the SIGNAL of the original thread with the corresponding
    // SLOT in this class
    connect(&thread, SIGNAL(started()),this, SLOT(run_thread()));
    connect(this, SIGNAL(finished()), &thread, SLOT(quit()));
    connect(&thread, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(&thread, SIGNAL(finished()), &thread, SLOT(deleteLater()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

}

// ========================================================================
// Implements the "run" method of a thread
// ========================================================================
void cc_read_data_thread::run_thread()
{
    qDebug() << "Establishing connection ...";

    // Initialise communication
    initialise_communication();

    qDebug() << "Connection establishing";

}

// ========================================================================
// In charge of initialising the communication/connection with the external
// data source
// ========================================================================
void cc_read_data_thread::initialise_communication()
{
    // -------------------------------------------------------------
    // Initialise socket
    // -------------------------------------------------------------
    if (Listener.listen(SOCKET_LISTEN_PORT_NUMBER) != sf::Socket::Done)
    {
        // ERROR
    }

    if (Listener.accept(Client) != sf::Socket::Done)
    {
        // Error...
    }

    Status = CONNECTED;

    emit finished();
}


