#include "lista.h"


Lista::Lista()
{
    primero = nullptr;
    cont = 0;
}


Lista::~Lista()
{
    //dtor
}


int Lista::getCont()
{
    return cont;
}


Nodo::Nodo()
{
    sig = nullptr;
}

Nodo::Nodo(Cuenta c)
{
    sig = nullptr;
    dato = c;
}

Nodo::~Nodo()
{

}


void Nodo::setSig(Nodo* sig)
{
    this->sig = sig;
}


void Nodo::setDato(Cuenta c)
{

    dato=c;
}

Nodo* Nodo::getSig()
{
    return this->sig;
}


Cuenta Nodo::getDato()
{
    return dato;
}




Cuenta Lista::operator[](int pos)
{
    Nodo* aux;
    aux = primero;
    for (int i = 0; i<pos; i++)
        aux = aux->getSig();
    return aux->getDato();
}


void Lista::inserta(Cuenta c)//recibe un objeto
{
    Nodo* nuevoNodo = new Nodo(c);//crea nuevo nodo del objeto
    nuevoNodo->setSig(primero);
    primero = nuevoNodo;
    cont++;
}


bool Lista::valida_usuario(string usr, string con)
{

    Nodo*aux = primero;

    while(aux!=nullptr)
    {
        Cuenta c;
        c=aux->getDato();
        if(usr==c.getusario()&& con==c.getcontra())
        {

           return true;

        }

        aux=aux->getSig();

    }



    return false;
}




bool Lista::es_doble(string usr)
{
    Nodo*aux=primero;
    while(aux!=nullptr)
    {
       Cuenta c;
        c=aux->getDato();
        if(usr==c.getusario())
        {

            return true;
        }


        aux = aux->getSig();

        //cout<<"Nombre:"<<c.getusername(); //el c objeto obtiene los datos de cada variable
    }
    return false;

}


void Lista::guardarEnDisco()
{

    ofstream fout("Cuentas.txt");


    Nodo* aux;
    aux = primero;
    for (int i = 0; i<cont; i++)
    {
        Cuenta c = aux->getDato();
        fout<< c.toFile()<<endl;//objeto de clase Cuenta
        aux = aux->getSig();
    }
    fout.close();
}


//Función para imprimir


void Lista::imprimir()
{
    //T1 es el objeto de Cuentas que contiene los nodos de lista
    Nodo* aux;
    aux = primero;
    cout<<"\nDatos en lista:"<<endl;
    while(aux!=nullptr)
    {
        Cuenta c;
        c = aux->getDato();
        aux = aux->getSig();

        cout<<" \n"<<c.toString()<<"\n";
        //cout<<"Nombre:"<<c.getusername(); //el c objeto obtiene los datos de cada variable
    }



}



void Lista::encuentra_usuario(string usr)
{
    Nodo* aux = primero;
    while(aux!=nullptr)
    {
        Cuenta c;
        c = aux->getDato();
        if(usr== c.getusario())
        {
            cout<<"Nombre:"<<c.getnombre()<<endl;
            cout<<"Usuario:"<<c.getusario()<<endl;
            cout<<"Correo:"<<c.getcorreo()<<endl;
        }
        aux = aux->getSig();
    }
}



void Lista::agregar_usuario(string nom,string usr,string corr,string cont)
{

    Cuenta a(usr,corr,nom,cont);
    inserta(a);


}



void Lista::elimina_usuario(string usr)
{
    int indice = localiza(usr);
    if(vacia() or indice == -1)
    {
        return;
    }
    if(indice == 0)
    {
        primero = primero->getSig();
        cont--;
    }
    else
    {
        int i = 0;
        Nodo*aux = primero;
        while(aux != nullptr)
        {
            if(i == indice-1)
            {
                Nodo*temp = aux;
                aux = aux->getSig();
                temp->setSig(aux->getSig());
                delete aux;
                cont--;
                break;
            }
            i++;
            aux = aux->getSig();
        }
    }
}

bool valid( string address )
{
    size_t at = address.rfind('@') ; // encuentra el ultimo '@'
    if( at == std::string::npos ) return false ; // no '@'

    size_t dot = address.find( '.', at ) ; // encuentra '.' después del ultimo '@'
    if( dot == std::string::npos ) return false ; // no '.' después de  '@'

    return dot < address.size() - 1 ; // verdadero si hay al menos un caracacter mas después del punto

}




void Lista:: modificar_usuario(string usr)
{


    if(vacia())
    {
        throw std::invalid_argument("Lista vacia");
    }
    else
    {

        int opt;
        Nodo* aux = primero;
        while(aux!=nullptr)
        {
            Cuenta c;
            c = aux->getDato();

            if(usr==c.getusario())
            {
                cout <<"Nombre:"<<c.getnombre()<< "\n";
                cout <<"Usuario:"<<c.getusario()<< "\n";
                cout <<"Correo:"<< c.getcorreo()<< "\n";
                cout <<"Contrasena:"<<c.getcontra()<< "\n";


                cout<<"1.Nombre\n2.Usuario\n3.Correo\n4.Contraseña"<<endl;
                cout<<"¿Cual dato deseas modificar?"<<endl;
                cin>>opt;


                if(opt==1)

                {
                    string n;
                    cout<<"Ingresa nombre: "<<endl;
                    cin>>n;
                    c.setnombre(n);
                    aux->setDato(c);
                }
                else if(opt==2)
                {
                    string u;

                    do
                    {
                        cout<<"Ingresa usuario: "<<endl;
                        cin>>u;
                        //getline(cin,u);


                        if (es_doble(u)==true)
                        {
                            system("cls");
                            cout << "Nombre de usuario no disponible, ingrese uno nuevo."<<endl;
                        }
                        else;
                    }
                    while(es_doble(u));
                    c.setusuario(u);
                    aux->setDato(c);
                }
                else if(opt==3)
                {
                    string co;
                    do
                    {
                        cout<<"Ingresa correo:"<<endl;
                        cin>>co;

                        if (valid (co)==false)
                        {
                            system("cls");
                            cout << "Correo invalido."<<endl;


                        }
                        else;
                    }
                    while(!valid(co));

                    c.setcorreo(co);
                    aux->setDato(c);

                }
                else if(opt==4)
                {
                    string con;
                    cout<<"Ingresa contrasena:"<<endl;
                    cin>>con;
                    c.setcorreo(con);
                    aux->setDato(c);
                }


            }
            aux = aux->getSig();

        }
    }

}






int Lista::localiza(string usr)
{
    Nodo* aux=primero;
    int indice = 0;
    while(aux!=nullptr)
    {
        if(usr== aux->getDato().getusario())
        {
            return indice;
        }
        indice++;
        aux=aux->getSig();
    }
    return -1;


}




bool Lista::vacia()
{
    return primero == nullptr;
}




//Carga archivo completo y lo mete a lista
void Lista::cargarDesdeDisco(string r)
{
    ifstream fin;
    fin.open(r);
    if(!fin.good())
    {
        cout<<"No existe el archivo (aun)"<<endl;
        ofstream out("Cuentas.txt");
    }
    string stringObj;
    fin>>stringObj;
    //cout<<"Cadenas cargadas:"<<endl;
    while(!fin.eof())
    {
        //cout<<"   "<<stringObj<<endl;
        Cuenta obj(stringObj);
        inserta(obj);
        fin>>stringObj;
    }
    fin.close();
}
