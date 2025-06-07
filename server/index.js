const express = require('express');
const bodyParser = require('body-parser');
const rippleEngine = require('./rippleEngine');

const app = express();
app.use(bodyParser.json());

app.use('/ripple', rippleEngine);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
