# Deploy to Render and Vercel

Push the deployment files to GitHub first.

1. In https://dashboard.render.com, create a new Blueprint and connect
   `Shreyansh-100/DecisionTreeCpp`. Render reads the root `render.yaml`.
   The backend uses the free plan and builds its C++ engine inside Docker.
   Set `ALLOWED_ORIGINS` to `http://localhost:5173` initially.
2. After the backend deploys, copy its HTTPS URL and visit `/health`.
   The response should be `{"status":"ok"}`.
3. In https://vercel.com/new, import the same repository. Set Root Directory
   to `frontend`. Build command: `npm run build`. Output directory: `dist`.
4. Add `VITE_API_URL` in Vercel with the Render HTTPS URL, without `/predict`,
   for Production (and Preview if needed). Deploy.
5. In Render, replace `ALLOWED_ORIGINS` with the exact Vercel production
   origin, such as `https://your-project.vercel.app`, then redeploy the backend.
   Multiple origins can be comma-separated. Add custom domains or specific
   preview origins here if you use them.
6. Upload `Dtree/read.csv` on the deployed frontend and confirm a CSV report
   downloads. Files are temporary and deleted after the response.

Changing `VITE_API_URL` requires a new frontend build. Keep deployment
credentials out of repository files. Free backend services may take time
to wake up after inactivity.

The API accepts CSV files up to 10 MiB and limits engine execution to 60
seconds. This remains a demo: its public endpoint has no authentication or
rate limiting, and the C++ parser expects the project's dataset format.

## Local Docker check

```bash
docker build -t decision-tree-api .
docker run --rm -p 10000:10000 -e ALLOWED_ORIGINS=http://localhost:5173 decision-tree-api
```

In another terminal:

```bash
curl http://localhost:10000/health
curl -f -F file=@Dtree/read.csv http://localhost:10000/predict -o /tmp/report.csv
```
