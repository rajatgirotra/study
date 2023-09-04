import express from 'express';
import {fileURLToPath} from 'url';
import {dirname, parse, sep} from 'path';
import compression from 'compression';
import formidable from 'formidable';
import {copyFileSync} from 'fs';
import {validationResult, check, oneOf} from 'express-validator';

const __dirname = dirname(fileURLToPath(import.meta.url)) + sep;

const cfg = {
    port: process.env.PORT || 8110,
    dir: {
        root: __dirname,
        static: __dirname + 'static' + sep,
        views: __dirname + 'views' + sep,
        uploads: __dirname + 'uploads' + sep,
    }
}

console.dir(cfg, {depth: null, color: true});

const validation = [check('email').exists().withMessage('email is required').isEmail().withMessage('email not valid')];

const app = express();

app.disable('x-powered-by');
app.set('view engine', 'ejs');
app.set('views', cfg.dir.views);
app.set('strict routing', false);
app.set('case sensitive routing', false);

// use compression for performance
app.use(compression());

// use static
app.use(express.static(cfg.dir.static));

// // middleware for storing uploaded files.
// app.use(express.u)

app.use((req, res, next) => {
    console.log(`received a new HTTP request for url ${req.url}`);
   next();
});

// create one endpoint
app.get('/', (req, res) => {
   res.render('formGET', {title: 'Parse HTTP GET Data',
   data: req.query});
});

app.all('/using_post_to_upload_file/', (req, res, next) => {
    if(req.method === 'GET' || req.method === 'POST') {
        // we create a formidable object by providing it a configuration.
        const form = formidable();
        // form.multiple = true;
        form.uploadDir = cfg.dir.uploads;
        form.keepExtensions = true;

        // now call parse function to parse the form data. and register a callback when data is parsed.
        form.parse(req, (err, data, files) => {
            // err will be set if there is any error
            // data will contain non-file parsed data (text boxes, checkbox etc, dropdowns etc)
            // files will contain the parsed file data (uploaded files)
            if(err) {
                next(err);
                return;
            }

            console.dir(files);
            // the key "image" on the files property is the element id of the input (type=image) element on the submitted form
            if(files && files.image && files.image[0].size > 0) {
                data.filename = files.image[0].originalFilename;
                data.filetype = files.image[0].mimetype;
                data.filesize = Math.ceil(files.image[0].size/1024) + ' KB';
                data.uploadto = files.image[0].filepath;
                // copy file from uploads to static folder as file will be served from there.
                copyFileSync(files.image[0].filepath, cfg.dir.static + parse(files.image[0].filepath).base); // we need to serve the image from static folder.
                data.imageurl = '/' + parse(files.image[0].filepath).base; // we use imageurl later.
            }

            res.render('formPOST_UPLOAD_FILE', {title: 'Parse HTTP POST file data', data})
        });
    } else {
        next();
    }
});

// install a new express middleware for parsing POST data in express. POST data is available on req.body parameter.
app.use(express.urlencoded({extended: true})); // extended: true will create a much Richer body property. so never a bad idea to use it.
app.all('/using_post/', (req, res, next) => {
    if(req.method === 'GET' || req.method === 'POST') {
        res.render('formPOST', {title: 'Parse HTTP POST Data',
            data: req.body}); // the req.body property is created by the express.urlencoded() middleware.
    } else {
        next();
    }
});


app.listen(cfg.port, () => {
    console.log(`server listening on port ${cfg.port}`);
});

export {cfg, app};
