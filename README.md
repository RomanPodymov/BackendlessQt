# BackendlessQt

Qt wrapper for [Backendless](https://backendless.com).

## How to use it?

Create a new API instance
```
API api(API("YOUR_APP_ID", "YOUR_REST_API_KEY"));
```

Register a new user
```
QObject::connect(&api, &API::userRegistered, [](){
    // User is registered
});
api.registerUser(BackendlessUser("myemail@email.com", "Roman", "Password"));
```

Sign in
```
QObject::connect(&api, &API::userSignedIn, [](){
    // User is signed in
});
api.signInUser("myemail@email.com", "Password");
```

Validate user token
```
QObject::connect(&api, &API::userTokenValidated, [](auto isValid){
    // Is user token valid?
});
api.validateUserToken();
```

Add a new item to a table
```
QObject::connect(&api, &API::itemAdded, [&](){
    // Item is added
});
api.addItemToTable(
    "TableName", 
    {
        {"propery", "value"}, 
        {"anotherProperty", "value"}
    }
);
```

Read table items
```
QObject::connect(&api, &API::tableItemsLoaded, [&](auto response){
    qDebug() << "Loaded " << response;
});
api.loadTableItems("TableName");
```
