import LiquidEther from './components/LiquidEther';
import './App.css';
import TextType from './components/TextType';
import BorderGlow from './components/BorderGlow';
import PillNav from './components/PillNav';
import ScrollStack, { ScrollStackItem } from './components/ScrollStack';
import logo from './assets/logo.jpg'
import { useState,useRef } from 'react';
import Terminal from './components/terminal/terminal';

function App() {
  const navItems = [
    { label: 'Home', href: '/' },
    { label: 'Model', href: '#model' },
    { label: 'Workflow', href: '#workflow' },
    { label: 'Contact', href: '#contact' }
  ];
  

  return (
    <div className="app">
      <div className="liquid-page" aria-hidden="true">
        <LiquidEther
          mouseForce={20}
          cursorSize={100}
          isViscous={false}
          viscous={30}
          colors={['#111827', '#06b6d4', '#d8b4fe']}
          autoDemo
          autoSpeed={0.5}
          autoIntensity={2.2}
          isBounce={false}
          resolution={0.4}
        />
      </div>

      <header className="menu">
        <PillNav
        logo={logo}
          logoAlt="logo"
          items={navItems}
          activeHref="/"
          className="custom-nav"
          ease="power2.easeOut"
          baseColor="#05070d63"
          pillColor="#4fc3d0"
          hoveredPillTextColor="#ffffff"
          pillTextColor="#05070d"
          initialLoadAnimation
        />
      </header>

      <main className="page-shell">
        <section className="hero-section" id="home">
          <div className="text-main">
            <p className="eyebrow">C++ decision tree classifier</p>
            <h1>
              <TextType
                text={[
                  'Train. Split. Predict.',
                  'A machine learning model built using C++.'
                ]}
                typingSpeed={90}
                pauseDuration={1500}
                showCursor
                cursorCharacter="|"
                deletingSpeed={35}
                cursorBlinkDuration={0.5}
              />
            </h1>
            <p className="hero-copy">
              A compact decision-tree project with a visual front end for explaining how raw data becomes a model, and how that model makes predictions.
              
            </p>
             
          </div>

          <div className="intro-text" id="model">
            <BorderGlow
              edgeSensitivity={28}
              glowColor="190 90 70"
              backgroundColor="rgba(8, 12, 22, 0.78)"
              borderRadius={24}
              glowRadius={36}
              glowIntensity={0.9}
              coneSpread={22}
              animated
              colors={['#22d3ee', '#c084fc', '#f8fafc']}
            >
              <div className="model-card">
                <div>
                  <p className="card-kicker">Model Snapshot</p>
                  <h2>Decision Tree Inference</h2>
                  <p>
                    Built around readable C++ modules for data handling, training, and inference.
                  </p>
                </div>
                <dl className="metric-grid">
                  <div>
                    <dt>Language</dt>
                    <dd>C++</dd>
                  </div>
                  <div>
                    <dt>Frontend</dt>
                    <dd>React</dd>
                  </div>
                  <div>
                    <dt>Pipeline</dt>
                    <dd>CSV to prediction</dd>
                  </div>
                </dl>
              </div>
            </BorderGlow>
          </div>
        </section>

        <section className="stack-section" id="workflow">
          <div className="section-heading">
            <p className="eyebrow">Workflow</p>
            <h2>How the model works</h2>
          </div>

          <ScrollStack
            className="stack"
            itemDistance={54}
            itemStackDistance={24}
            stackPosition="18%"
            baseScale={0.9}
            useWindowScroll
          >
            <ScrollStackItem itemClassName="workflow-card workflow-card-one">
              <span>01</span>
              <h3>Load the dataset</h3>
              <p>Read CSV rows into a clean shape before the model starts choosing branches.</p>
            </ScrollStackItem>
            <ScrollStackItem itemClassName="workflow-card workflow-card-two">
              <span>02</span>
              <h3>Split by information</h3>
              <p>The tree compares candidate features and builds decisions that separate outcomes.The current model leverages the Gini Entropy to build the decision tree</p>
            </ScrollStackItem>
            <ScrollStackItem itemClassName="workflow-card workflow-card-three">
              <span>03</span>
              <h3>Run inference</h3>
              <p>New samples travel down the trained tree until they reach a predicted class.</p>
            </ScrollStackItem>

            <ScrollStackItem itemClassName="workflow-card workflow-card-three">
              <span>04</span>
              <h3>Compute error metrics</h3>
              <p>The module computes Precision,Recall and F1 score to help you evaluate the model's performance.USE THE MODEL FOR BINARY CLASSIFICATION  </p>
            </ScrollStackItem>
          </ScrollStack>
        </section>
        


         <section className="contact-section" id="contact">
          <h2>Ready for experiments</h2>
          <p>Use this shell and let the module perform the necessary computations required to build your model and output the file containing the required predictions</p>
        </section>

        <div className='terminal'>
          <Terminal/>
        </div>

       
      </main>
    </div>
  );
}

export default App;
