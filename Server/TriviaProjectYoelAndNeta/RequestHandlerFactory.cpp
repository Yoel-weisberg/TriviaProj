#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) , m_loginManager(db), m_statisticsManager()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
    delete m_database;
    m_database = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler( m_loginManager,*this);
}

LoginManager& RequestHandlerFactory::GetLoginManager()
{    
    return LoginManager::getInstance(this->m_database);
}

IDatabase* RequestHandlerFactory::getDatabase()
{
    return m_database;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(*this, user.getUsername(), m_roomManager);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}
