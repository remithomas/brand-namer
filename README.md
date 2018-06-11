# Brand namer... [![CircleCI](https://circleci.com/gh/remithomas/brand-namer.svg?style=svg)](https://circleci.com/gh/remithomas/brand-namer)

**Brand namer** because brand name availability it's so complicated 😭

> Currently in WIP

The project is simply: type your _term_, and the system gives you the availabled names (or their synonymes) in some languages for the domain `.com` and `Facebook`

- This project is/will be coded with love in [ReasonMl](http://reasonml.github.io/)
  - Backend: ExpressJs with [bs-express](https://github.com/reasonml-community/bs-express)
  - Frontend: ReactJs on [ReasonReact](https://reasonml.github.io/reason-react/)

- This is a Isomorphic App: it integrates backend and frontend.

## Requirements

* bs-platform `3.1.4`
* node `8.*`
* gcloud api token
* Facebook oauth token
* AWS access key (and secret)

### Installation

Create a `.env` file to your root folder using [.env.sample](./.env.sample) file sample

```bash
yarn install
```

### Development

BSB Development
```bash
yarn start
```

Javascript Development (read only)
```bash
# backend
yarn run nodemon

# frontend
yarn run build:dev
```

test
```bash
yarn test
```

Open [http://127.0.0.1:3000/](http://127.0.0.1:3000) url in your browser.

## How it works

This is simple, you ask a name and the API send you some possible translations and synonyms with their avaibility for `Facebook` and `.com`.

### Under the hood

- [`server` folder](./server/): source of the nodejs application
- [`common` folder](./common): shared tool and type
- [`src` folder](./src/): source of the React app

## Todos (Stories)

- [X] Front-end setup
- [X] Back-end setup
- [X] Send request to API
- [X] Show translations (and languages)
- [X] Api ask if domain exists (route 53)
- [X] Api ask if facebook name exists
- [ ] Handle error from aws (improvement)
- [ ] A bit of design (check mark etc...)

## Thanks

* Many thanks to [@Glennsl](https://github.com/glennsl) with his awesome lib [bs-json](https://github.com/glennsl/bs-json)
* icons are coming from [https://iconmonstr.com](https://iconmonstr.com)
