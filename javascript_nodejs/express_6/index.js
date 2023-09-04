import express from 'express';
import compression from 'compression';
import {fileURLToPath} from 'url';
import {sep, dirname} from 'path';
import {helloRouter} from "./routes/hello.js";

const __dirname = dirname(fileURLToPath(import.meta.url)) + sep
const cfg = {
    port: (process.env.PORT || 8110),
    dir: {
        root: __dirname,
        static: __dirname + "static" + sep,
        views: __dirname + "views" + sep
    }
};

console.dir(cfg, {depth: null, color: true});

const app = express();
app.set('case sensitive routing', false);
app.set('strict routing', false);
app.disable('x-powered-by');
app.set('view engine', 'ejs');
app.set('views', cfg.dir.views);


app.use(compression()); // compress responses for performance

app.use((req, res, next) => {
    console.log(`a new http request received with url: ${req.url}`);
    next();
});

// set up static directory
app.use(express.static(cfg.dir.static));

app.get('/', (req, res) => {
    res.render('message', {title: 'Hello World!'});
});

app.use('/hello/', helloRouter);

// last middleware for page not found
app.use((req, res, next) => {
   res.status(404).send('Error! Page not found');
});

app.listen(cfg.port, () => {
    console.log(`server listening on port ${cfg.port}`);
});

export {cfg, app};