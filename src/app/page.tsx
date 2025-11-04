"use client"

import { useState } from "react"
import SearchCard from "./search-card"
import ResultsCard from "./results-card"

export default function Home() {
  const [zipCode, setZipCode] = useState("")
  const [results, setResults] = useState(null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState("")
  const [treeType, setTreeType] = useState<"red-black" | "b-tree">("red-black")

  const handleSearch = async (code: string) => {
    setZipCode(code)
    setLoading(true)
    setError("")
    setResults(null)

    // Simulate API call to backend (Red-Black Tree or B-Tree search)
    setTimeout(() => {
      // Mock data - in production, this would call your backend
      const mockData: Record<string, any> = {
        "10001": {
          state: "New York",
          city: "New York",
          metro: "New York-Newark-Jersey City",
          county: "New York",
          avgPrice: 895000,
        },
        "90210": {
          state: "California",
          city: "Beverly Hills",
          metro: "Los Angeles-Long Beach-Anaheim",
          county: "Los Angeles",
          avgPrice: 3250000,
        },
        "77001": {
          state: "Texas",
          city: "Houston",
          metro: "Houston-The Woodlands-Sugar Land",
          county: "Harris",
          avgPrice: 385000,
        },
        "60601": {
          state: "Illinois",
          city: "Chicago",
          metro: "Chicago-Naperville-Elgin",
          county: "Cook",
          avgPrice: 425000,
        },
      }

      if (mockData[code]) {
        setResults(mockData[code])
      } else {
        setError(`No data found for zip code: ${code}`)
      }
      setLoading(false)
    }, 800)
  }

  return (
    <main className="min-h-screen bg-gradient-to-b from-blue-50 to-white">
      <div className="px-[100px] py-12">
        {/* Header */}
        <div className="mb-12">
          <h1 className="text-5xl font-bold text-slate-900 mb-4 text-center">Home Price Estimator</h1>
          <p className="text-xl text-slate-600 text-center">
            Search by zip code to discover average home prices and location details across the US
          </p>
        </div>

        <div className="mb-8">
          <div className="bg-white rounded-lg border border-slate-200 shadow-sm p-4">
            <p className="text-sm font-medium text-slate-700 mb-3">Search Algorithm</p>
            <div className="flex gap-3">
              <button
                onClick={() => setTreeType("red-black")}
                className={`flex-1 px-4 py-2 rounded-lg font-medium transition-colors ${
                  treeType === "red-black" ? "bg-blue-600 text-white" : "bg-slate-100 text-slate-700 hover:bg-slate-200"
                }`}
              >
                Red-Black Tree
              </button>
              <button
                onClick={() => setTreeType("b-tree")}
                className={`flex-1 px-4 py-2 rounded-lg font-medium transition-colors ${
                  treeType === "b-tree" ? "bg-blue-600 text-white" : "bg-slate-100 text-slate-700 hover:bg-slate-200"
                }`}
              >
                B-Tree
              </button>
            </div>
          </div>
        </div>

        {/* Search and Results - Single Column */}
        <div className="space-y-8">
          <SearchCard onSearch={handleSearch} loading={loading} treeType={treeType} />
          <ResultsCard results={results} loading={loading} error={error} zipCode={zipCode} />
        </div>
      </div>
    </main>
  )
}
