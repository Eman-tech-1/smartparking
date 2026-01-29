#include "crow_all.h"
#include "ParkingSystem.h"
#include <string>

int main() {
    crow::SimpleApp app;
    ParkingSystem sys(5);

    CROW_ROUTE(app, "/")([&sys](){
        std::string html = "<html><head><title>Smart Parking Pro</title><style>";
        html += "body { font-family: sans-serif; background: #f4f7f6; padding: 20px; }";
        html += ".container { max-width: 1000px; margin: auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 4px 15px rgba(0,0,0,0.1); }";
        html += "nav { display: flex; gap: 10px; margin-bottom: 20px; justify-content: center; }";
        html += "nav button { padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; background: #3498db; color: white; }";
        html += ".zone-grid { display: grid; grid-template-columns: repeat(5, 1fr); gap: 10px; margin-bottom: 20px; }";
        html += ".zone-card { border: 2px solid #3498db; padding: 10px; border-radius: 8px; text-align: center; }";
        html += "table { width: 100%; border-collapse: collapse; } th, td { padding: 10px; border: 1px solid #ddd; }";
        html += ".page { display: none; } .active { display: block; }";
        html += "</style></head><body>";

        html += "<div class='container'><h1>🚗 Smart Parking System</h1>";
        
        html += "<nav><button onclick=\"showPage('zones')\">Occupancy</button>";
        html += "<button onclick=\"showPage('book')\">Book Slot</button>";
        html += "<button onclick=\"showPage('logs')\">Records</button></nav>";

        // Zones Page
        html += "<div id='zones' class='page active'><h3>Zone Occupancy</h3><div class='zone-grid'>";
        for(int i=0; i<5; i++) {
            html += "<div class='zone-card'><b>Zone " + std::to_string(i) + "</b><br><span style='font-size:24px'>" + std::to_string(sys.getZoneCount(i)) + "</span></div>";
        }
        html += "</div></div>";

        // Booking Page
        html += "<div id='book' class='page'><h3>New Booking</h3>";
        html += "<form action='/allocate' method='post'>";
        html += "Name: <input type='text' name='name' required><br><br>";
        html += "CNIC: <input type='text' name='cnic' required><br><br>";
        html += "Plate: <input type='text' name='vid' required><br><br>";
        html += "Zone (0-4): <input type='number' name='zone' min='0' max='4' required><br><br>";
        html += "<button type='submit' style='background:#2ecc71; color:white; border:none; padding:10px; width:100%'>Confirm</button></form></div>";

        // Logs Page
        html += "<div id='logs' class='page'><h3>Parking Logs</h3><table><thead><tr><th>Name</th><th>Plate</th><th>Zone</th></tr></thead><tbody>";
        for(int i=0; i < sys.getVehicleCount(); i++) {
            Vehicle* v = sys.getVehicleAt(i);
            if(v) {
                html += "<tr><td>" + v->getOwnerName() + "</td><td>" + v->getVehicleID() + "</td><td>" + std::to_string(v->getPreferredZone()) + "</td></tr>";
            }
        }
        html += "</tbody></table>";
        html += "<form action='/rollback' method='post'><button type='submit' style='background:#e74c3c; color:white; border:none; padding:10px; margin-top:10px'>Undo Last</button></form></div>";

        html += "</div><script>function showPage(id){document.querySelectorAll('.page').forEach(p=>p.classList.remove('active')); document.getElementById(id).classList.add('active');}</script></body></html>";
        
        crow::response res(html);
        res.set_header("Content-Type", "text/html");
        return res;
    });

    CROW_ROUTE(app, "/allocate").methods("POST"_method)([&sys](const crow::request& req){
        auto params = crow::query_string("?" + req.body);
        std::string vid = params.get("vid");
        if (sys.isVehicleAlreadyParked(vid)) return crow::response("Already Parked");
        
        Vehicle v(vid, params.get("name"), params.get("cnic"), std::stoi(params.get("zone")));
        sys.processParking(v);
        
        crow::response res;
        res.code = 303; res.set_header("Location", "/");
        return res;
    });

    CROW_ROUTE(app, "/rollback").methods("POST"_method)([&sys](){
        sys.performRollback();
        crow::response res;
        res.code = 303; res.set_header("Location", "/");
        return res;
    });

    app.port(18080).run();
}