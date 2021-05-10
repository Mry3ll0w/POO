#ifndef USUARIO-PEDIDO_HPP
#define USUARIO-PEDIDO_HPP
#include <map> 
#include <set> 
class Pedido; 
class Usuario; 
class Usuario_Pedido{ 
    public: 

/* ------------------------------ diccionarios ------------------------------ */
        typedef std::set<Pedido*> Pedidos; 
        typedef std::map<Usuario*, Pedidos> User_Ped; 
        typedef std::map<Pedido*, Usuario*> Ped_User; 

/* ------------------------------ asociaciones ------------------------------ */
        void asocia(Usuario& u, Pedido& p){
            user_ped_[&u].insert(&p);//usuario--> pedido
            ped_user_[&p] = &u;//pedido-->usuario
        } 
        void asocia(Pedido& p, Usuario& u){
            asocia(u, p);
        } 
        Usuario* cliente(Pedido& p){
            return ped_user_.find(&p)->second;
        } 
        Pedidos& pedidos(Usuario& u){
            return user_ped_.find(&u)->second;
        }  
    private: 
        User_Ped user_ped_; 
        Ped_User ped_user_; 

};
#endif
