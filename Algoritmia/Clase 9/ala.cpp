#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Civilizacion {
private:
    std::string nombre_;
    int ubicacion_x_;
    int ubicacion_y_;
    int puntuacion_;
public:
    Civilizacion(std::string nombre, int ubicacion_x, int ubicacion_y, int puntuacion) :
        nombre_(nombre), ubicacion_x_(ubicacion_x), ubicacion_y_(ubicacion_y), puntuacion_(puntuacion) {}
    std::string getNombre() const {
        return nombre_;
    }
    int getUbicacionX() const {
        return ubicacion_x_;
    }
    int getUbicacionY() const {
        return ubicacion_y_;
    }
    int getPuntuacion() const {
        return puntuacion_;
    }
};

class VideoGame {
private:
    std::string usuario_;
    std::vector<Civilizacion> civilizaciones_;
public:
    void setUsuario(std::string usuario) {
        usuario_ = usuario;
    }

    void agregarCivilizacion(const Civilizacion& c) {
        civilizaciones_.push_back(c);
    }
    void insertarCivilizacion(const Civilizacion& c, int posicion) {
        if (posicion < 0 || posicion > civilizaciones_.size()) {
            std::cout << "Posicion invalida.\n";
            return;
        }
        civilizaciones_.insert(civilizaciones_.begin() + posicion, c);
    }
    void ordenarPorNombre() {
        std::sort(civilizaciones_.begin(), civilizaciones_.end(), [](const Civilizacion& c1, const Civilizacion& c2) {
            return c1.getNombre() < c2.getNombre();
        });
    }
    void ordenarPorUbicacionX() {
        std::sort(civilizaciones_.begin(), civilizaciones_.end(), [](const Civilizacion& c1, const Civilizacion& c2) {
            return c1.getUbicacionX() < c2.getUbicacionX();
        });
    }
    void ordenarPorUbicacionY() {
        std::sort(civilizaciones_.begin(), civilizaciones_.end(), [](const Civilizacion& c1, const Civilizacion& c2) {
            return c1.getUbicacionY() < c2.getUbicacionY();
        });
    }
    void ordenarPorPuntuacion() {
        std::sort(civilizaciones_.begin(), civilizaciones_.end(), [](const Civilizacion& c1, const Civilizacion& c2) {
            return c1.getPuntuacion() > c2.getPuntuacion();
        });
    }
    void eliminarCivilizacionPorNombre(std::string nombre) {
        auto it = std::find_if(civilizaciones_.begin(), civilizaciones_.end(), [&](const Civilizacion& c) {
            return c.getNombre() == nombre;
        });
        if (it != civilizaciones_.end()) {
            civilizaciones_.erase(it);
            std::cout << "Civilizacion eliminada.\n";
        } else {
            std::cout << "Civilizacion no encontrada.\n";
        }
    }
    Civilizacion* buscarCivilizacionPorNombre(std::string nombre) {
        auto it = std::find_if(civilizaciones_.begin(), civilizaciones_.end(), [&](const Civilizacion& c) {
            return c.getNombre() == nombre;
        });
        if (it != civilizaciones_.end()) {
            return &(*it);
        }
    }
};