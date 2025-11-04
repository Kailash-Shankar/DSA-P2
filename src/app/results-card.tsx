"use client"

import { Home, MapPin, Building2, DollarSign } from "lucide-react"

interface ResultsCardProps {
  results: {
    state: string
    city: string
    metro: string
    county: string
    avgPrice: number
  } | null
  loading: boolean
  error: string
  zipCode: string
}

export default function ResultsCard({ results, loading, error, zipCode }: ResultsCardProps) {
  return (
    <div className="bg-white rounded-lg border border-slate-200 shadow-sm p-8">
      <h2 className="text-2xl font-bold text-slate-900 mb-6">Results</h2>

      {!zipCode && !loading && !error && (
        <div className="flex flex-col items-center justify-center py-12 text-center">
          <Home className="h-12 w-12 text-slate-300 mb-4" />
          <p className="text-slate-500">Enter a zip code to see property data and pricing information</p>
        </div>
      )}

      {loading && (
        <div className="flex flex-col items-center justify-center py-12">
          <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-blue-600 mb-4"></div>
          <p className="text-slate-600">Searching our database...</p>
        </div>
      )}

      {error && (
        <div className="bg-red-50 border border-red-200 rounded-lg p-4">
          <p className="text-red-800 font-medium">{error}</p>
          <p className="text-red-700 text-sm mt-1">Please verify the zip code and try again</p>
        </div>
      )}

      {results && zipCode && (
        <div className="space-y-4">
          {/* Zip Code Header */}
          <div className="bg-blue-50 border border-blue-200 rounded-lg p-4 mb-6">
            <p className="text-sm text-blue-600 font-medium">Zip Code</p>
            <p className="text-3xl font-bold text-blue-900">{zipCode}</p>
          </div>

          {/* Results Grid */}
          <div className="grid grid-cols-1 gap-4">
            {/* State */}
            <div className="border border-slate-200 rounded-lg p-4 hover:border-blue-300 transition-colors">
              <div className="flex items-center gap-2 mb-2">
                <MapPin className="h-5 w-5 text-blue-600" />
                <p className="text-sm font-medium text-slate-700">State</p>
              </div>
              <p className="text-lg font-semibold text-slate-900">{results.state}</p>
            </div>

            {/* City */}
            <div className="border border-slate-200 rounded-lg p-4 hover:border-blue-300 transition-colors">
              <div className="flex items-center gap-2 mb-2">
                <Building2 className="h-5 w-5 text-blue-600" />
                <p className="text-sm font-medium text-slate-700">City</p>
              </div>
              <p className="text-lg font-semibold text-slate-900">{results.city}</p>
            </div>

            {/* County */}
            <div className="border border-slate-200 rounded-lg p-4 hover:border-blue-300 transition-colors">
              <div className="flex items-center gap-2 mb-2">
                <MapPin className="h-5 w-5 text-blue-600" />
                <p className="text-sm font-medium text-slate-700">County</p>
              </div>
              <p className="text-lg font-semibold text-slate-900">{results.county}</p>
            </div>

            {/* Metro Area */}
            <div className="border border-slate-200 rounded-lg p-4 hover:border-blue-300 transition-colors">
              <div className="flex items-center gap-2 mb-2">
                <MapPin className="h-5 w-5 text-blue-600" />
                <p className="text-sm font-medium text-slate-700">Metro Area</p>
              </div>
              <p className="text-lg font-semibold text-slate-900">{results.metro}</p>
            </div>

            {/* Average Price */}
            <div className="border-2 border-blue-300 bg-blue-50 rounded-lg p-4">
              <div className="flex items-center gap-2 mb-2">
                <DollarSign className="h-5 w-5 text-blue-600" />
                <p className="text-sm font-medium text-blue-700">Average Home Price</p>
              </div>
              <p className="text-2xl font-bold text-blue-900">${results.avgPrice.toLocaleString()}</p>
            </div>
          </div>
        </div>
      )}
    </div>
  )
}
