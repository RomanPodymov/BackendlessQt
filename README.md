# BackendlessQt

Qt wrapper for [Backendless](https://backendless.com).

## How to use it?

Create a new API instance
```
AnyNetworkAccessManager* networkManager;
BackendlessAPI* api;

int main(int argc, char *argv[]) {
    QApplication myApp(argc, argv);

    networkManager = new StandardNetworkManager();
    api = new BackendlessAPI(
        networkManager,
        QSharedPointer<BackendlessSignInUserCoder>(new BackendlessSignInUserCoder()),
        "YOUR_APP_ID",
        "YOUR_REST_API_KEY"
    );
}
```

Register a new user
```
QObject::connect(&api->userAPI, &BackendlessUserAPI::registerUserResult, this, []() {
    // User is registered
});
BackendlessRegisterUserRepresentable* currentUser = new BackendlessRegisterUser("myemail@email.com", "Password", "name");
api->userAPI.registerUser(*currentUser);
```

Sign in
```
QObject::connect(&api->userAPI, &BackendlessUserAPI::signInUserSuccess, this, []() {
    // User is signed in
});
QObject::connect(&api->userAPI, &BackendlessUserAPI::signInUserErrorBackendless, this, []() {
    // Wrong credentials
});
api->userAPI.signInUser("myemail@email.com", "Password");
```
