const express = require('express');
const router = express.Router();
const Product = require('../../controllers/product');
const Login = require('../../controllers/login');
const Key = require('../../controllers/key');
const multer = require('multer');
var randomstring = require("randomstring");
var path = require('path');
var cors = require('cors');
const storage = multer.diskStorage({
    destination: function(req, file, cb) {
        cb(null, './uploads/');
    },
    filename: function(req, file, cb) {
        console.log(file);
        cb(null, randomstring.generate(9) + new Date().getMilliseconds() + path.extname(file.originalname));
    }
});
const upload = multer({storage: storage});


var corsOptions = {
    origin: '*'
}

var cyclic = "2";

router.get("/set/:cycle", cors(corsOptions), async(req, res) => {
    try {
        cyclic = req.params.cycle;
        res.json(req.params.cycle);
    } catch (err) {
        console.error("error: ", err);
        res.json(err);
    }
});

router.get("/get", cors(corsOptions), async(req, res) => {
    try {
        res.json(cyclic);
    } catch (err) {
        console.error("error: ", err);
        res.json(err);
    }
});

module.exports = router;