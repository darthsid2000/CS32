void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m == nullptr)
        return;
    if (path == "")
        path += m->name();
    else
        path = path + "/" + m->name();
    if (path != "")
        cout << path << endl;
    if (m->menuItems() != nullptr)
        for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
            listAll(*it, path);
}
