var express = require("express");
var app = express();
var pg = require("pg");
var fs = require("fs");

var dbString = "postgres://bcenergiabrasil2:lambda255@postgresql01.bcenergiabrasil.hospedagemdesites.ws/bcenergiabrasil2";

app.set("views", "./views");
app.set("view engine", "pug");

app.get("/", function(req, res) {
    pg.connect(dbString, function(conErr, client, done) {
        client.query("SELECT id, nome FROM estados", function(qErr, result) {
            fs.readFile("./linked_list.h", "utf-8", function(fErr, fileData) {
                res.render("index", {estados: result.rows, arquivo: fileData});
            })
        });
    });
});

app.listen(4000, function() {
    console.log("Listening");
});
